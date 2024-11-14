#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an item with weight and value
struct Item
{
    int weight;
    int value;
};

// Comparator function to sort items based on value-to-weight ratio
bool compare(Item a, Item b)
{
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

// Function to calculate maximum value we can get with given capacity
double fractionalKnapsack(int capacity, vector<Item> items)
{
    // Sort items by value-to-weight ratio
    sort(items.begin(), items.end(), compare);

    double totalValue = 0.0;

    for (auto &item : items)
    {
        if (capacity >= item.weight)
        { // Take whole item if it fits
            capacity -= item.weight;
            totalValue += item.value;
        }
        else
        { // Take fraction of the item
            totalValue += item.value * ((double)capacity / item.weight);
            break; // Knapsack is full
        }
    }

    return totalValue;
}

int main()
{
    int capacity = 50;
    vector<Item> items = {{10, 60}, {20, 100}, {30, 120}};

    double maxValue = fractionalKnapsack(capacity, items);

    cout << "Maximum value we can obtain = " << maxValue << endl;

    return 0;
}
