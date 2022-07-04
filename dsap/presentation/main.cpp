#include <iostream>
#include <vector>

struct node
{
    size_t l, r;                  // l , r represent the range of all the child leaves
    int sum;                      // represent the sum within [l,r]
    size_t leftChild, rightChild; // represent the location of chil leaves;
    node(size_t inputL, size_t inputR)
    {
        l = inputL;
        r = inputR;
    }
};

void buildTree(size_t addr, std::vector<struct node> &tree, std::vector<int> &val)
{
    // addr represent the location of current node
    if (tree.at(addr).l == tree.at(addr).r)
    {
        tree.at(addr).sum = val.at(tree.at(addr).l);
        return; // reach buttom
    }
    size_t middle = (tree.at(addr).l + tree.at(addr).r) / 2;
    struct node leftChildNode(tree.at(addr).l, middle);
    tree.push_back(leftChildNode);
    tree.at(addr).leftChild = tree.size() - 1;
    buildTree(tree.at(addr).leftChild, tree, val); // build left sub tree

    struct node rightChildNode(middle + 1, tree.at(addr).r);
    tree.push_back(rightChildNode);
    tree.at(addr).rightChild = tree.size() - 1;
    buildTree(tree.at(addr).rightChild, tree, val);// build right sub tree
    tree.at(addr).sum = tree.at(tree.at(addr).leftChild).sum + tree.at(tree.at(addr).rightChild).sum;
    // sum[l,r] = sum[l , a]+sum[a+1 , r]
    return;
}

void updateTree(size_t addr, size_t changeLocation, std::vector<struct node> &tree, std::vector<int> &val)
{
    if (tree.at(addr).l == tree.at(addr).r)
    {
        tree.at(addr).sum = val.at(tree.at(addr).l);
        return;
    }
    size_t middle = (tree.at(addr).l + tree.at(addr).r) / 2;
    if (changeLocation > middle)
    {
        updateTree(tree.at(addr).rightChild, changeLocation, tree, val);
    }
    else
    {
        updateTree(tree.at(addr).leftChild, changeLocation, tree, val);
    }
    tree.at(addr).sum = tree.at(tree.at(addr).leftChild).sum + tree.at(tree.at(addr).rightChild).sum;
    return;
}

void updateValue(size_t addr, int value, std::vector<struct node> &tree, std::vector<int> &val)
{
    val.at(addr) = value;
    updateTree(0, addr, tree, val);
    return;
}

int getRangeSum(size_t rangeL, size_t rangeR, size_t addr, std::vector<struct node> &tree)
{
    if (rangeL <= tree.at(addr).l && rangeR >= tree.at(addr).r)
    {
        return tree.at(addr).sum;
    }
    size_t middle = (tree.at(addr).l + tree.at(addr).r) / 2;
    int result = 0;
    if (rangeR > middle)
    {
        result += getRangeSum(rangeL, rangeR, tree.at(addr).rightChild, tree);
    }
    if (rangeL <= middle)
    {
        result += getRangeSum(rangeL, rangeR, tree.at(addr).leftChild, tree);
    }
    return result;
}

int main()
{
    std::vector<int> val = {1, 3, 2, 1, 6, 5};
    std::vector<struct node> tree;
    struct node root(0, val.size() - 1);
    tree.push_back(root);
    buildTree(0, tree, val);
    std::cout << getRangeSum(0, 0, 0, tree) << std::endl;
    std::cout << getRangeSum(0, 5, 0, tree) << std::endl;
    std::cout << getRangeSum(2, 4, 0, tree) << std::endl;
    updateValue(0, 100, tree, val);
    std::cout << getRangeSum(0, 5, 0, tree) << std::endl;
    return 0;
}
