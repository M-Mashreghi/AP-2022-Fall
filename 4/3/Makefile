MAKE = sudo g++ -c
BUILD_DIR = build
BACKEND_DIR = backend

 OBJECT_FILES = $(BUILD_DIR)/server.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/Purchased_card.o $(BUILD_DIR)/Category_filter.o \
				$(BUILD_DIR)/Rate_filter.o $(BUILD_DIR)/Price_filter.o $(BUILD_DIR)/total_cost_offer.o $(BUILD_DIR)/Offer_package.o \
				$(BUILD_DIR)/Offer_category.o $(BUILD_DIR)/Offer.o $(BACKEND_DIR)/Main.cpp $(BUILD_DIR)/Buyer.o $(BUILD_DIR)/Seller.o \
				$(BUILD_DIR)/Item.o  $(BUILD_DIR)/Purchased.o $(BUILD_DIR)/UTkala.o $(BUILD_DIR)/Read_input.o \
				$(BUILD_DIR)/Consts.o  $(BUILD_DIR)/User.o $(BUILD_DIR)/response.o $(BUILD_DIR)/utilities.o \
				$(BUILD_DIR)/template_parser.o $(BUILD_DIR)/request.o $(BUILD_DIR)/route.o


utkala.out  : $(OBJECT_FILES)
	sudo g++ $(OBJECT_FILES) --std=c++11 -o utkala.out


$(BUILD_DIR)/handlers.o: $(BUILD_DIR)/UTkala.o $(BACKEND_DIR)/handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	sudo g++ -c $(BACKEND_DIR)/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/UTkala.o: $(BACKEND_DIR)/UTkala.cpp $(BACKEND_DIR)/UTkala.hpp
	$(MAKE)  $(BACKEND_DIR)/UTkala.cpp -o $(BUILD_DIR)/UTkala.o

$(BUILD_DIR)/Purchased_card.o: $(BACKEND_DIR)/Purchased_card.cpp $(BACKEND_DIR)/Purchased_card.hpp
	$(MAKE)  $(BACKEND_DIR)/Purchased_card.cpp -o $(BUILD_DIR)/Purchased_card.o

$(BUILD_DIR)/Purchased.o: $(BACKEND_DIR)/Purchased.cpp $(BACKEND_DIR)/Purchased.hpp
	$(MAKE)  $(BACKEND_DIR)/Purchased.cpp -o $(BUILD_DIR)/Purchased.o

$(BUILD_DIR)/Category_filter.o: $(BACKEND_DIR)/Category_filter.cpp $(BACKEND_DIR)/Category_filter.hpp
	$(MAKE)  $(BACKEND_DIR)/Category_filter.cpp -o $(BUILD_DIR)/Category_filter.o

$(BUILD_DIR)/Rate_filter.o: $(BACKEND_DIR)/Rate_filter.cpp $(BACKEND_DIR)/Rate_filter.hpp
	$(MAKE)  $(BACKEND_DIR)/Rate_filter.cpp -o $(BUILD_DIR)/Rate_filter.o

$(BUILD_DIR)/Price_filter.o: $(BACKEND_DIR)/Price_filter.cpp $(BACKEND_DIR)/Price_filter.hpp
	$(MAKE)  $(BACKEND_DIR)/Price_filter.cpp -o $(BUILD_DIR)/Price_filter.o



$(BUILD_DIR)/total_cost_offer.o: $(BACKEND_DIR)/total_cost_offer.cpp $(BACKEND_DIR)/total_cost_offer.hpp
	$(MAKE)  $(BACKEND_DIR)/total_cost_offer.cpp -o $(BUILD_DIR)/total_cost_offer.o

$(BUILD_DIR)/Offer_package.o: $(BACKEND_DIR)/Offer_package.cpp $(BACKEND_DIR)/Offer_package.hpp
	$(MAKE)  $(BACKEND_DIR)/Offer_package.cpp -o $(BUILD_DIR)/Offer_package.o

$(BUILD_DIR)/Offer_category.o: $(BACKEND_DIR)/Offer_category.cpp $(BACKEND_DIR)/Offer_category.hpp
	$(MAKE)  $(BACKEND_DIR)/Offer_category.cpp -o $(BUILD_DIR)/Offer_category.o

$(BUILD_DIR)/Offer.o: $(BACKEND_DIR)/Offer.cpp $(BACKEND_DIR)/Offer.hpp
	$(MAKE) $(BACKEND_DIR)/Offer.cpp -o $(BUILD_DIR)/Offer.o

$(BUILD_DIR)/Item.o: $(BACKEND_DIR)/Item.cpp $(BACKEND_DIR)/Item.hpp
	$(MAKE)  $(BACKEND_DIR)/Item.cpp -o $(BUILD_DIR)/Item.o

$(BUILD_DIR)/Seller.o : $(BACKEND_DIR)/Seller.cpp $(BACKEND_DIR)/Seller.hpp
	$(MAKE) $(BACKEND_DIR)/Seller.cpp -o $(BUILD_DIR)/Seller.o

$(BUILD_DIR)/Buyer.o: $(BACKEND_DIR)/Buyer.cpp $(BACKEND_DIR)/Buyer.hpp
	$(MAKE) $(BACKEND_DIR)/Buyer.cpp -o $(BUILD_DIR)/Buyer.o

$(BUILD_DIR)/User.o : $(BACKEND_DIR)/User.cpp $(BACKEND_DIR)/User.hpp
	$(MAKE)  $(BACKEND_DIR)/User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/Consts.o: $(BACKEND_DIR)/Consts.cpp $(BACKEND_DIR)/Consts.hpp
	$(MAKE)  $(BACKEND_DIR)/Consts.cpp -o $(BUILD_DIR)/Consts.o

$(BUILD_DIR)/Read_input.o: $(BACKEND_DIR)/Read_input.cpp $(BACKEND_DIR)/Read_input.hpp
	$(MAKE)  $(BACKEND_DIR)/Read_input.cpp -o $(BUILD_DIR)/Read_input.o





$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(MAKE) server/server.cpp -o $(BUILD_DIR)/server.o


$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(MAKE) utils/utilities.cpp -o $(BUILD_DIR)/utilities.o
	
$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(MAKE) utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o



$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(MAKE) utils/request.cpp -o $(BUILD_DIR)/request.o


$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(MAKE) utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(MAKE) server/route.cpp -o $(BUILD_DIR)/route.o