#pragma once
#include <vector>
#include "resident.hpp"

namespace rbtree {
    enum Color {
        RED,
        BLACK
    };

    struct tnode {
        Color color;
        Resident data;
        tnode* parent;
        tnode* left;
        tnode* right;

        tnode(Color color, Resident data, tnode* parent, tnode* left, tnode* right) : 
            color(color), data(data), parent(parent), left(left), right(right) {}
    };

    /**
    * @brief Класс, реализующий RB дерево
    * 
    * Все функции написаны в соответствии с алгоритмами из книги Кормена
    */
    class RBTree {
        private:
        tnode* root;
        tnode* Tnil;

        /**
        * @brief Операция Left-Rotate
        */
        void leftRotate(tnode* x) {
            tnode* y = x->right;
            x->right = y->left;

            if (y->left != Tnil) {
                y->left->parent = x;
            }
            y->parent = x->parent;
            if (x->parent == Tnil) {
                root = y;
            } else if (x == x->parent->left) {
                x->parent->left = y;
            } else {
                x->parent->right = y;
            }

            y->left = x;

            x->parent = y;
        }

        /**
        * @brief Операция Right-Rotate
        */
        void rightRotate(tnode* x) {
            tnode* y = x->left;
            x->left = y->right;

            if (y->right != Tnil) {
                y->right->parent = x;
            }
            y->parent = x->parent;
            if (x->parent == Tnil) {
                root = y;
            } else if (x == x->parent->right) {
                x->parent->right = y;
            } else {
                x->parent->left = y;
            }

            y->right = x;

            x->parent = y;
        }

        /**
        * @brief Исправление КБ дерева после вставки узла
        */
        void RBInsertFixup(tnode* input) {
            tnode* y;

            while (input->parent->color == Color::RED) {
                if (input->parent == input->parent->parent->left) {
                    y = input->parent->parent->right;
                    if (y->color == Color::RED) {
                        input->parent->color = Color::BLACK;
                        y->color = Color::BLACK;
                        input->parent->parent->color = Color::RED;
                        input = input->parent->parent;
                    } else {
                        if (input == input->parent->right) {
                            input = input->parent;
                            leftRotate(input);
                        }

                        input->parent->color = Color::BLACK;
                        input->parent->parent->color = Color::RED;
                        rightRotate(input->parent->parent);
                    }
                } else {
                    y = input->parent->parent->left;
                    if (y->color == Color::RED) {
                        input->parent->color = Color::BLACK;
                        y->color = Color::BLACK;
                        input->parent->parent->color = Color::RED;
                        input = input->parent->parent;
                    } else {
                        if (input == input->parent->left) {
                            input = input->parent;
                            rightRotate(input);
                        }

                        input->parent->color = Color::BLACK;
                        input->parent->parent->color = Color::RED;
                        leftRotate(input->parent->parent);
                    }
                }
            }

            root->color = Color::BLACK;
        }


        void deleteTree(tnode *node) {
            if (node != Tnil) {
                deleteTree(node->left);
                deleteTree(node->right);
                delete node;
            }
        }

        /**
        * @brief Вспомогательная функция для поиска по RB дереву
        */
        void searchLoop(tnode* node, const std::string& key, std::vector<Resident>& result) {
            if (node == Tnil) {
                return;
            }

            if (node->data.street == key) {
                result.push_back(node->data);
                searchLoop(node->left, key, result);
                searchLoop(node->right, key, result);
            } else if (key < node->data.street) {
                searchLoop(node->left, key, result);
            } else {
                searchLoop(node->right, key, result);
            }
        }

        // -------------------------
        public:
        RBTree() {
            Tnil = new tnode(Color::BLACK, Resident(), nullptr, nullptr, nullptr);
            root = Tnil;
        }

        ~RBTree() {
            deleteTree(root);
            delete Tnil;
        }

        /**
        * @brief Функция для вставки узла в RB дерево
        */
        void RBInsert(const Resident& data) {
            tnode* input = new tnode(Color::RED, data, nullptr, Tnil, Tnil);

            tnode* y = Tnil;
            tnode* x = root;

            while (x != Tnil) {
                y = x;
                if (input->data < x->data) {
                    x = x->left;
                } else {
                    x = x->right;
                }
            }

            input->parent = y;

            if (y == Tnil) {
                root = input;
            } else if (input->data < y->data) {
                y->left = input;
            } else {
                y->right = input;
            }

            input->left = Tnil;
            input->right = Tnil;
            input->color = Color::RED;

            RBInsertFixup(input);
        }

        /**
        * @brief Функция для поиска по RB дереву
        */
        std::vector<Resident> search(const std::string& key) {
            std::vector<Resident> result;

            searchLoop(root, key, result);

            return result;
        }
    };
}
