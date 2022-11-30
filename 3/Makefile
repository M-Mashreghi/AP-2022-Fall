a.out : main.cpp School.o Course_unit_request.o sign_up_rules.o  Student.o Class.o
	sudo g++ -c  Class.o Course_unit_request.o  School.o sign_up_rules.o Student.o main.cpp

School.o: School.cpp School.hpp
	sudo g++ -c  School.cpp


Course_unit_request.o : Course_unit_request.cpp Course_unit_request.hpp
	sudo g++ -c Course_unit_request.cpp


sign_up_rules.o: sign_up_rules.cpp sign_up_rules.hpp
	sudo g++ -c sign_up_rules.cpp



Student.o : Student.cpp Student.hpp
	sudo g++ -c  Student.cpp


Class.o: Class.cpp Class.hpp
	sudo g++ -c  Class.cpp
