#pragma once
#include <string>
#include <map>



struct Discount {
	int nbrOfItems;
	int discountPrice;
};
class Checkout
{
public:
	Checkout();
	~Checkout();
	void addItem(std::string itemName);
	void addItemPrice(std::string itemName,int value);
	void addDiscount(std::string itemName, int nbrItems, int discountedPrice);
	
	int calculateTotal();

protected:
	std::map<std::string, int> prices;
	std::map<std::string, int> items;
	std::map<std::string, Discount> discounts;
	void calculateItem(std::string item, int itemCount);
	void calculateDiscount(std::string item, int itemCnt, Discount discount);
	int total;
};

