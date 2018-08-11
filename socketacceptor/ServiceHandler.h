#include "Poco/Net/SocketReactor.h"
#include "Poco/Net/SocketNotification.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/NObserver.h"
#include "Poco/Exception.h"
#include "Poco/Thread.h"

#include <iostream>

using Poco::Net::SocketReactor;
using Poco::Net::ReadableNotification;
using Poco::Net::ShutdownNotification;
using Poco::Net::StreamSocket;
using Poco::Util::Application;
using Poco::NObserver;
using Poco::AutoPtr;
using Poco::Thread;


class ServiceHandler
{
public:
	ServiceHandler(StreamSocket& socket, SocketReactor& reactor);
	~ServiceHandler();
	void onReadable(const AutoPtr<ReadableNotification>& pNf);
	void onShutdown(const AutoPtr<ShutdownNotification>& pNf);
	
private:
	enum
	{
		BUFFER_SIZE = 1024
	};
	
	StreamSocket   _socket;
	SocketReactor& _reactor;
	char*          _pBuffer;
};
