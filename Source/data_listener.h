#pragma once
#ifndef data_listener_h
# define data_listener_h

# include <iostream>
# include <string>

class data_listener
{
public:
	//pure virtual fonksiyon
	// bu siniftan dogrudan nesne olusturulamaz.
	// arayuz veya temel sinif olarak kullanilir.
	virtual void onDataReceived(const std::string& message) = 0;
};

#endif