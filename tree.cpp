#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>

struct TreeNode {
    TreeNode* left;
    TreeNode* right;
    int value;
};
void PreOrder(TreeNode* root) {
    std::stack<TreeNode*> s;
    TreeNode* p = root;
    while (p != NULL || !s.empty()) {
        while (p != NULL) {
            std::cout << p->value << " ";
            s.push(p);
            p = p->left;
        }
        if (!s.empty()) {
            p = s.top();
            s.pop();
            p = p->right;
        }
    }
    std::cout << std::endl;
}

void InOrder(TreeNode* root) {
    std::stack<TreeNode*> s;
    TreeNode* p = root;
    while (p != NULL || !s.empty()) {
        while (p != NULL) {
            s.push(p);
            p = p->left;
        }
        if (!s.empty()) {
            p = s.top();
            std::cout << p->value << " ";
            s.pop();
            p = p->right;
        }
    }
    std::cout << std::endl;
}

void PostOrder(TreeNode* root) {
    std::stack<TreeNode*> s;
    TreeNode* cur;
    TreeNode* pre = NULL;
    if (root != NULL) {
        s.push(root);
    }
    while (!s.empty()) {
        cur = s.top();
        if (((cur->left == NULL) && (cur->right == NULL)) ||
          ((pre != NULL) && ((pre == cur->left) || (pre == cur->right)))) {
            std::cout << cur->value << " ";
            s.pop();
            pre = cur;
        } else {
            if (cur->right != NULL) {
                s.push(cur->right);
            }
            if (cur->left != NULL) {
                s.push(cur->left);
            }
        }
    }
    std::cout << std::endl;
}

void LevelOrder(TreeNode* root) {
    std::queue<TreeNode*> q;
    TreeNode* p;
    if (root != NULL) {
        q.push(root);
    }
    while (!q.empty()) {
        p = q.front();
        std::cout << p->value << " ";
        q.pop();
        if (p->left != NULL) {
            q.push(p->left);
        }
        if (p->right != NULL) {
            q.push(p->right);
        }
    }
    std::cout << std::endl;
}
int GetNodeNum(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    return GetNodeNum(root->left) + GetNodeNum(root->right) + 1;
}

int GetHeight(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    return std::max(GetHeight(root->left), GetHeight(root->right)) + 1;

}

bool IsAVL(TreeNode* root, int& height) {
    if (root == NULL) {
        height = 0;
        return true;
    }
    int left_height;
    bool is_left_avl = IsAVL(root->left, left_height);
    int right_height;
    bool is_right_avl = IsAVL(root->right, right_height);
    height = std::max(left_height, right_height) + 1;
    if (is_left_avl && is_right_avl && (left_height-right_height) <= 1 && (right_height-left_height) <= 1) {
        return true;
    }
    return false;
}


void ConvertToDLink(TreeNode* root, TreeNode*& first, TreeNode*& last) {
    if (root == NULL) {
        first = NULL;
        last = NULL;
        return;
    }
    TreeNode* left_first;
    TreeNode* left_last;
    if (root->left == NULL) {
        first = root;
    } else {
        ConvertToDLink(root->left, left_first, left_last);
        first = left_first;
        root->left = left_last;
        left_last->right = root;
    }


    TreeNode* right_first;
    TreeNode* right_last;
    if (root->right == NULL) {
        last = root;
    } else {
        ConvertToDLink(root->right, right_first, right_last);
        last = right_last;
        root->right = right_first;
        right_first->left = root;
    }
}

TreeNode* Mirror(TreeNode* root) {
    if (root == NULL) {
        return NULL;
    }
    TreeNode* left = Mirror(root->left);
    TreeNode* right = Mirror(root->right);
    root->left = right;
    root->right = left;
    return root;
}

TreeNode* FindCommonParent(TreeNode* root, int a, int b) {
    if (root == NULL) {
        return NULL;
    }
    if (root->value == a || root->value == b) {
        return root;
    }
    TreeNode* left = FindCommonParent(root->left, a, b);
    TreeNode* right = FindCommonParent(root->right, a, b);
    if (left != NULL && right != NULL) {
        return root;
    }
    return left != NULL ? left : right;
}

TreeNode* BuildTree(int value, int level) {
    if (level >= 3) {
        return NULL;
    }
    std::cout << "build value: " << value << std::endl;
    TreeNode* root = new TreeNode;
    root->value = value;
    root->left = BuildTree(value * 2 + 0, level + 1);
    root->right = BuildTree(value * 2 + 1, level + 1);
    return root;
}

TreeNode* BuildTree2(int value, int level) {
    if (level >= 3) {
        return NULL;
    }
    std::cout << "build value: " << value << std::endl;
    TreeNode* root = new TreeNode;
    root->value = value;
    root->left = BuildTree(value * 2 + 0, level + 1);
    root->right = NULL;
    return root;
}

void DestoryTree(TreeNode* root) {
   if (root == NULL) {
       return;
   }
   if (root->left != NULL) {
       DestoryTree(root->left);
   }
   if (root->right != NULL) {
       DestoryTree(root->right);
   }
   delete root;
   root = NULL;
}

int main() {
    TreeNode* root = BuildTree(1, 0);
    TreeNode* root2 = BuildTree2(1, 0);
    PreOrder(root);
    TreeNode* mirror_root = Mirror(root);
    PreOrder(mirror_root);
    InOrder(root);
    PostOrder(root);
    LevelOrder(root);
    std::cout << "Node num: " << GetNodeNum(root) << std::endl;
    std::cout << "Height: " << GetHeight(root) << std::endl;
    TreeNode* first;
    TreeNode* last;
    ConvertToDLink(root, first, last);
    TreeNode* p = first;
    while(p != NULL) {
        std::cout << p->value << " ";
        p = p->right;
    }
    std::cout << std::endl;
    p = last;
    while(p != NULL) {
        std::cout << p->value << " ";
        p = p->left;
    }
    std::cout << std::endl;
    int height1;
    std::cout << "is avl: " << IsAVL(root, height1) << std::endl;
    int height2;
    std::cout << "is avl: " << IsAVL(root2, height2) << std::endl;
    TreeNode* p1 = FindCommonParent(root, 4, 5);
    std::cout << p1->value << std::endl;
    TreeNode* p2 = FindCommonParent(root, 4, 7);
    std::cout << p2->value << std::endl;
    TreeNode* p3 = FindCommonParent(root, 4, 2);
    std::cout << p3->value << std::endl;
    DestoryTree(root);
    DestoryTree(root2);
    return 0;
}
