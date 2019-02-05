#include "stdafx.h"
#include "Checkout.h"


Checkout::Checkout() :total(0)
{
}

Checkout::~Checkout()
{
}

void Checkout::addItemPrice(std::string itemName, int price)
{
	prices[itemName] = price;
}

void Checkout::addItem(std::string itemName)
{
	std::map<std::string, int>::iterator priceIter = prices.find(itemName);
	if (priceIter == prices.end()) {
		throw std::invalid_argument("Invalid item.  No price");
	}
	items[itemName]++;
}

void Checkout::addDiscount(std::string item, int nbrOfItems, int discountPrice) {
	Discount discount;
	discount.nbrOfItems = nbrOfItems;
	discount.discountPrice = discountPrice;
	discounts[item] = discount;
}
int Checkout::calculateTotal()
{
	total = 0;
	for (std::map<std::string, int>::iterator itemIter = items.begin();
		itemIter != items.end(); itemIter++) {
		std::string item = itemIter->first;
		int itemCount = itemIter->second;
		calculateItem(item, itemCount);
	}
	return total;
}

void Checkout::calculateItem(std::string item, int itemCount) {
	std::map<std::string, Discount>::iterator discountIter;
	discountIter = discounts.find(item);
	if (discountIter != discounts.end()) {
		Discount discount = discountIter->second;
		calculateDiscount(item, itemCount, discount);
	}
	else {
		total += itemCount * prices[item];
	}
}

void Checkout::calculateDiscount(std::string item, int itemCnt, Discount discount) {
	if (itemCnt >= discount.nbrOfItems) {
		int nbrOfDiscounts = itemCnt / discount.nbrOfItems;
		total += nbrOfDiscounts * discount.discountPrice;
		int remainingItems = itemCnt % discount.nbrOfItems;
		total += remainingItems * prices[item];
	}
	else {
		total += itemCnt * prices[item];
	}
}