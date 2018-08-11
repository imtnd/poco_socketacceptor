#include "Server.h"


Server::Server()
{
}

Server::~Server()
{
}

int Server::main(const std::vector<std::string>& args)
{
	// get parameters from configuration file
	//unsigned short port = (unsigned short) config().getInt("Server.port", 9977);
	unsigned short port = (unsigned short)9977;
	
	// set-up a server socket
	ServerSocket svs(port);
	// set-up a SocketReactor...
	SocketReactor reactor;
	// ... and a SocketAcceptor
	ParallelSocketAcceptor<ServiceHandler, SocketReactor> acceptor(svs, reactor);
	// run the reactor in its own thread so that we can wait for 
	// a termination request
	Thread thread;
	thread.start(reactor);
	// wait for CTRL-C or kill
	waitForTerminationRequest();
	// Stop the SocketReactor
	reactor.stop();
	thread.join();
	
	return Application::EXIT_OK;
}
