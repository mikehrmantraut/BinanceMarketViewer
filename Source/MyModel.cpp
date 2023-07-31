#include "MyModel.h"

void MyModel::run()
{
	MyAsyncHttpSession ses;
	ses.run([this](const std::string& res)
        {
            response = res;
            if (view)
                view->update();
        });
}
