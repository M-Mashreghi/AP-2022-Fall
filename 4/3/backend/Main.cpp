
#include "handlers.hpp"

using namespace std;

int main() {
	UTkala* UTKALA;
    Server server(8080);
    server.get("/", new ShowPage("static/home.html"));
    server.get("/signup", new ShowPage("static/signup.html"));
	server.post("/signup", new SignupHandler(UTKALA));
    server.run();
}


#include "handlers.hpp"

