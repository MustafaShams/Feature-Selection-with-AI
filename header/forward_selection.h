#ifndef CS170_PROJECT_2_FORWARD_SELECTION_H
#define CS170_PROJECT_2_FORWARD_SELECTION_H

//#include <bits/stdc++.h>
#include "Node.h"
#include "Tree.h"

using namespace std;

//Greedy Forward Selection
class Select {
public:
    Node* root;
    vector<int> feats;
    string filename;
    int num_features;
    Validator *validator;
    int selected; //total number of features that were selected

    Select(int num_feats, string file) {
        root = new Node();
        filename = file;
        num_features = num_feats;
        for (int i = 0; i < num_feats; i++)
            feats.push_back(i + 1);
    }

    void forwardSelect() {
        Tree *tree = new Tree(root);
        validator = new Validator;
        validator->initDataset(filename);
        root->set_FS_Accuracy(validator->initRootAccuracy());

        if (num_features == 0) {
            pickChild(tree);
            cout << "Finished search!" << endl;
            return;
        }
        for (int i = 0; i < num_features; i++) {
            expandChildren(tree);
            if (!pickChild(tree)) {
                cout << "Finished search!" << endl;
                return;
            }
        }
    }

    void expandChildren(Tree* tree) {
        int feature_size;
        vector<int> new_features;
        Node* currNode = tree->currNode;
        feature_size = tree->currNode->curr_features.size();


        if (feature_size < num_features) {
            new_features = validFeatures(currNode, feature_size);
            for (int i = 0; i < num_features - feature_size; i++) {
                Node* newNode = new Node(tree->currNode);
                newNode->addFeature(new_features.at(i));
                currNode->children.push_back(newNode);
            }
//            Validator *validator = new Validator;
            for (int i = 0; i < currNode->children.size(); i++) {
                currNode->children.at(i)->set_FS_Accuracy(validator->leave_one_out_validation(currNode->children.at(i)->curr_features, filename, 1));
                cout << "Using feature(s) ";
                currNode->children.at(i)->printFeats();
                cout << " accuracy is " << currNode->children.at(i)->accuracy << endl;
            }
            cout << "\n";
        }
    }

    bool pickChild(Tree* tree) {
        bool child_chosen = false;
        Node* currNode = tree->currNode;
        Node* maxNode = tree->currNode;
        for (int i = 0; i < currNode->children.size(); i++) {
            if (maxNode->accuracy <= tree->currNode->children.at(i)->accuracy) {
                maxNode = currNode->children.at(i);
                child_chosen = true;
            }
        }

        tree->currNode = maxNode;
        cout << "Feature set ";
        tree->currNode->printFeats();
        cout << " was the best, accuracy is " << tree->currNode->accuracy << endl;
        return child_chosen;
    }




    vector<int> validFeatures(Node* currNode, int feature_size) {
        vector<int> new_feature;
        vector<int> invalid_feats;
        bool invalid;

        if (feature_size == 0) {
            for (int i = 0; i < num_features; i++)
                new_feature.push_back(feats.at(i));
        }

        else if (feature_size < num_features) {
            for (int i = 0; i < feature_size; i++)
                invalid_feats.push_back(currNode->curr_features.at(i));
            for (int i = 0; i < num_features; i++) {
                invalid = false;
                for (int j = 0; j < feature_size; j++) {
                    if (invalid_feats.at(j) == feats.at(i))
                        invalid = true;
                }
                if (!invalid)
                    new_feature.push_back(feats.at(i));

            }
        }
        return new_feature;
    }
};

#endif