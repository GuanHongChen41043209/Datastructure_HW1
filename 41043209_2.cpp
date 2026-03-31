#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

struct TreeNode{
    int key;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int k){
        key = k;
        left = nullptr;
        right = nullptr;
    }
};

TreeNode* Insert(TreeNode* root, int x, bool& inserted){
    if(root == nullptr){
        inserted = true;
        return new TreeNode(x);
    }
    if(x < root->key){
        root->left = Insert(root->left, x, inserted);
    }
    else if(x > root->key){
        root->right = Insert(root->right, x, inserted);
    }
    else{
        inserted = false;
    }
    return root;
}

int Height(TreeNode* root){
    if(root == nullptr){
        return 0;
    }
    int leftHeight = Height(root->left);
    int rightHeight = Height(root->right);
    if(leftHeight > rightHeight){
        return 1 + leftHeight;
    }
    else{
        return 1 + rightHeight;
    }
}

TreeNode* FindMin(TreeNode* root, int& steps){
    if(root == nullptr){
        return nullptr;
    }
    while(root->left != nullptr){
        steps++;
        root = root->left;
    }
    return root;
}

TreeNode* Delete(TreeNode* root, int k, int& steps){
    steps++;
    if(root == nullptr){
        return nullptr;
    }
    if(k < root->key){
        root->left = Delete(root->left, k, steps);
    }
    else if(k > root->key){
        root->right = Delete(root->right, k, steps);
    }
    else{
        if(root->left == nullptr && root->right == nullptr){
            delete root;
            return nullptr;
        }
        else if(root->left == nullptr){
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }
        else if(root->right == nullptr){
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }
        else{
            TreeNode* temp = FindMin(root->right, steps);
            root->key = temp->key;
            root->right = Delete(root->right, temp->key, steps);
        }
    }
    return root;
}

bool Search(TreeNode* root, int k){
    if(root == nullptr){
        return false;
    }
    if(k == root->key){
        return true;
    }
    else if(k < root->key){
        return Search(root->left, k);
    }
    else{
        return Search(root->right, k);
    }
}

int main(){
    srand(5);
    int values[] = {100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    int numTests = 12;
    int testTimes = 100;
    TreeNode* root = nullptr;
    cout << boolalpha;
    cout << "test Times = " << testTimes << endl;
    for(int i = 0; i < numTests; i++){
        int n = values[i];
        double totalHeight = 0.0;
        double totalRatio = 0.0;
        for(int t = 0; t < testTimes; t++){
            root = nullptr;
            int count = 0;
            while(count < n){
                int x = rand() % n;
                bool inserted = false;
                root = Insert(root, x, inserted);
                if(inserted){
                    count++;
                }
            }
            int h = Height(root);
            totalHeight += h;
        }
        double averageHeight = totalHeight / testTimes;
        double Ratio = averageHeight / log2(n);
        cout << "n = " << n
             << ",\taverage Height = " << averageHeight
             << ",\theight/log2(n) = " << Ratio << endl;
    }
    cout << "0 exists before delete:" << Search(root, 0) << endl;
    int steps = 0;
    root = Delete(root, 0, steps);
    cout << "Delete '0' steps = " << steps << endl;
    cout << "0 exists after delete:" << Search(root, 0) << endl;
    return 0;
}
