#include "Poco/Net/SocketReactor.h"
#include "Poco/Net/ParallelSocketAcceptor.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/HelpFormatter.h"
#include "ServiceHandler.h"

using Poco::Net::SocketReactor;
using Poco::Net::ParallelSocketAcceptor;
using Poco::Net::ServerSocket;
using Poco::Util::ServerApplication;
using Poco::Util::OptionSet;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::HelpFormatter;

class Server: public Poco::Util::ServerApplication
{
public:
	Server();
	~Server();
	
protected:
	int main(const std::vector<std::string>& args);
};