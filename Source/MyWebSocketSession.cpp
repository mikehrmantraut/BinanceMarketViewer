#include "MyWebSocketSession.h"

//singleton

int MyWebSocketSession::run(std::function <void(const std::string& message)> cb){
    try
    {
        std::thread([this,cb]() {
            std::string host = "stream.binance.com";
            auto const  port = "443";
            net::io_context ioc;
            ssl::context ctx{ssl::context::tlsv12_client};
            load_root_certificates(ctx);
            tcp::resolver resolver{ioc};
            websocket::stream<beast::ssl_stream<tcp::socket>> ws{ioc, ctx};
            auto const results = resolver.resolve(host, port);
            auto ep = net::connect(get_lowest_layer(ws), results);
            if (!SSL_set_tlsext_host_name(ws.next_layer().native_handle(), host.c_str()))
                throw beast::system_error(
                    beast::error_code(
                        static_cast<int>(::ERR_get_error()),
                        net::error::get_ssl_category()),
                    "Failed to set SNI Hostname");
            host += ':' + std::to_string(ep.port());
            ws.next_layer().handshake(ssl::stream_base::client);
            ws.set_option(websocket::stream_base::decorator(
                [](websocket::request_type& req)
                {
                    req.set(http::field::user_agent,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                    " websocket-client-coro");
                }));
            std::vector<beast::websocket::stream<beast::tcp_stream>> websockets;
            ws.handshake(host, "/ws/!miniTicker@arr");
            while (true)
            {
                beast::flat_buffer buffer;
                ws.read(buffer);
                std::string message = beast::buffers_to_string(buffer.data());
                std::lock_guard<std::recursive_mutex> lock(protect_listeners);
                {
                    for (const auto& item : listeners)
                    {
                        if (item)
                        {
                            try {
                                // mesaji socketten modele tasima islemi
                                item->onDataReceived(message);
                            }
                            catch (...)
                            {
                                std::cout << "Message did not received.";
                            }
                        }
                        
                    }
                }
                cb(message); 
            }
            }).detach();
        // detach, main thread ile bizim olusturdugumuz threadin bagimsiz bir sekilde
        // calismasini saglar. main thread de arkada islerini yurutmeye devam eder. bu threadin
        // bitmesini beklemez.

    }
    catch (std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
void MyWebSocketSession::addListener(data_listener* aListener) {
    std::lock_guard<std::recursive_mutex> lock(protect_listeners);
    listeners.push_back(aListener);
}
