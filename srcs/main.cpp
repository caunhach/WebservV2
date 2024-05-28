#include "./Server/Server.hpp"
#include "./Server/ServerManager.hpp"
#include "./Config/Config.hpp"

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		try {
			ServerManager serverManager;
			Config config;
			config.parse(argv[1]);
			serverManager.SetupServers(config);
			serverManager.RunServers();
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}
	else
	{
		std::cout << "Invalid number of arguments" << std::endl;
	}
}