// Assign09-InventoryArray.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
	// parallel array items loaded from inventory file
	string	itemCode[20];
	double	itemPrice[20];
	int		itemOnHand[20];
	string	itemName[20];

	int		itemCount = 0;
	int		purchaseCount = 0;
	int		pos;
	const	double	MARKUP_RATE = 0.18;

	//fields loaded from Purchases input file
	string	purchaseNum;
	string	purchaseItem;
	int		purchaseQty;
	double	purchaseTotal;

	ifstream inventoryFile;
	ifstream purchaseFile;
	ofstream inventoryUpdate;

	inventoryFile.open("Inventory.txt");
	purchaseFile.open("Purchases.txt");

	if (!inventoryFile || !purchaseFile)
	{
		cout << endl << "Error opening input file." << endl << endl;
		system("pause");
		return -1;
	}
	purchaseFile.close();

	inventoryFile >> itemCode[itemCount];

	// Load inventory data into parallel arrays
	while (!inventoryFile.eof())
	{
		inventoryFile >> itemPrice[itemCount] >> itemOnHand[itemCount] >> itemName[itemCount];

		itemCount++;
		inventoryFile >> itemCode[itemCount];
	}
	inventoryFile.close();

	cout << endl << itemCount << "  items loaded from inventory." << endl;

	//modify itemPrice[] values
	for (int i = 0; i < itemCount; i++)
	{
		itemPrice[i] = itemPrice[i] + (itemPrice[i] * MARKUP_RATE);
	}

	// process Purchases
	purchaseFile.open("Purchases.txt");

	purchaseFile >> purchaseNum;

	while (!purchaseFile.eof())
	{
		purchaseFile >> purchaseItem >> purchaseQty;
		purchaseCount++;
		//lookup by purchaseItem
		pos = 0;
		while (purchaseItem != itemCode[pos])
		{
			pos++;
		}
		if (purchaseItem == itemCode[pos])
		{
			purchaseTotal = itemPrice[pos] * purchaseQty;
			itemOnHand[pos] -= purchaseQty;
			cout << fixed << setprecision(2);
			cout << endl << purchaseNum << "  " << itemCode[pos] << setw(7) << right << purchaseQty << "  @ " << setw(10) << right << itemPrice[pos] << setw(10) << right << purchaseTotal << "  " << itemName[pos];
		}
		purchaseFile >> purchaseNum;
	}

	cout << endl << endl << purchaseCount << "  purchase records processed." << endl;

	inventoryUpdate.open("InventoryUpdate.txt");

	for (int pos = 0; pos < itemCount; pos++)
	{
		inventoryUpdate << itemCode[pos] << '\t' << itemPrice[pos] << '\t' << itemOnHand[pos] << '\t' << itemName[pos] << endl;
	}

	inventoryUpdate.close();
		
	cout << endl;
	system("pause");
	return 0;
}

