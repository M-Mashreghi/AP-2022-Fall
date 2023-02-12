MAKE = sudo g++ -c
BUILD_DIR = build
BACKEND_DIR = backend
 



utkala.out  :$(BUILD_DIR)/Purchased_card.o $(BUILD_DIR)/Category_filter.o $(BUILD_DIR)/Rate_filter.o $(BUILD_DIR)/Price_filter.o $(BUILD_DIR)/total_cost_offer.o $(BUILD_DIR)/Offer_package.o $(BUILD_DIR)/Offer_category.o $(BUILD_DIR)/Offer.o $(BACKEND_DIR)/Main.cpp $(BUILD_DIR)/Buyer.o $(BUILD_DIR)/Seller.o $(BUILD_DIR)/Item.o  $(BUILD_DIR)/Purchased.o $(BUILD_DIR)/UTkala.o $(BUILD_DIR)/Read_input.o $(BUILD_DIR)/Consts.o  $(BUILD_DIR)/User.o
	sudo g++  $(BUILD_DIR)/Purchased_card.o $(BUILD_DIR)/Category_filter.o $(BUILD_DIR)/Rate_filter.o $(BUILD_DIR)/Price_filter.o $(BUILD_DIR)/total_cost_offer.o $(BUILD_DIR)/Offer_package.o $(BACKEND_DIR)/Main.cpp $(BUILD_DIR)/Offer_category.o $(BUILD_DIR)/Buyer.o $(BUILD_DIR)/Seller.o $(BUILD_DIR)/Offer.o $(BUILD_DIR)/Item.o $(BUILD_DIR)/Purchased.o $(BUILD_DIR)/UTkala.o $(BUILD_DIR)/Read_input.o $(BUILD_DIR)/Consts.o  $(BUILD_DIR)/User.o  --std=c++11 -o utkala.out



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

