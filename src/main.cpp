#include <iostream>
#include <exception>

#include "CGFapplication.h"
#include "DemoScene.h"
#include "TPinterface.h"

using std::cout;
using std::exception;


int main(int argc, char* argv[]) {

	CGFapplication app = CGFapplication();

	try {
		app.init(&argc, argv);

		app.setScene(new DemoScene());
		//app.setInterface(new CGFinterface());
		app.setInterface(new TPinterface());

		app.run();
	}
	catch(GLexception& ex) {
		cout << "Error: " << ex.what();
	system("PAUSE");
		return -1;
	}
	catch(exception& ex) {
		cout << "Unexpected error: " << ex.what();
		system("PAUSE");

		return -1;
	}

	return 0;
}