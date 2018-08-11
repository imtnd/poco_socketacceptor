#include "ServiceHandler.h"


ServiceHandler::ServiceHandler(StreamSocket& socket, SocketReactor& reactor):
	_socket(socket),
	_reactor(reactor),
	_pBuffer(new char[BUFFER_SIZE])
{
	Application& app = Application::instance();
	app.logger().information("Connection from " + socket.peerAddress().toString());

	_reactor.addEventHandler(_socket, NObserver<ServiceHandler, ReadableNotification>(*this, &ServiceHandler::onReadable));
	_reactor.addEventHandler(_socket, NObserver<ServiceHandler, ShutdownNotification>(*this, &ServiceHandler::onShutdown));
}

ServiceHandler::~ServiceHandler()
{
	Application& app = Application::instance();
	try
	{
		app.logger().information("Disconnecting " + _socket.peerAddress().toString());
	}
	catch (...)
	{
	}
	_reactor.removeEventHandler(_socket, NObserver<ServiceHandler, ReadableNotification>(*this, &ServiceHandler::onReadable));
	_reactor.removeEventHandler(_socket, NObserver<ServiceHandler, ShutdownNotification>(*this, &ServiceHandler::onShutdown));
	delete [] _pBuffer;
}

void ServiceHandler::onReadable(const AutoPtr<ReadableNotification>& pNf)
{
	int n = _socket.receiveBytes(_pBuffer, BUFFER_SIZE);
	char o[3];
	memset(o,0x00,sizeof(o));
	
	if (n > 0){
		for (int i = 0; i < 30; i++){
			std::snprintf(o,3,"%2d",i);
			_socket.sendBytes(&o,3);
			sleep(1);
		}
	}
	else{
		delete this;
	}
}

void ServiceHandler::onShutdown(const AutoPtr<ShutdownNotification>& pNf)
{
	delete this;
}