#ifndef BACKWARD_ELIM_H
#define BACKWARD_ELIM_H

//#include <bits/stdc++.h>
#include "Node.h"
#include "Tree.h"

using namespace std;

//Greedy Backward Elimination
class Eliminate {
public:
    Node* root;
    //vector<int> feats = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40};
    vector<int> feats;
    vector<int> new_features;   //features in child nodes (one feature each)
    float default_acc = 0.0;    //accuracy for the root
    int num_features;       //number of features used in the tree
    int high_node = 0;    //locate the node with the highest accuracy in the given group of children
    float max_acc = 0.0;  //highest overall accuracy
    string filename;
    Validator *validator;
    
    int eliminated = 0; //total number of features that were eliminated
    float accuracy[66]; //array of all accuracies found during the greedy search; not counting root
    float compare_acc[40]; //variable used to compare accuracy of each child and find/hold the highest in each group
    int str_vfeat; //variable used to store feature before it is removed from subset to be verified

    int nAcc = 0;   //number of total greedy accuracies
    int drate_valid = 0;  //default rate validation
    int compare_cnt2 = 0;                       // counter variables
    int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0; //

    
    Eliminate(int num_feats, string file) {
        root = new Node();
        filename = file;
        num_features = num_feats;
        for (int i = 0; i < num_feats; i++)
            feats.push_back(i + 1);
    }

    void backwardEliminate() {
        Tree *tree = new Tree(root);
        validator = new Validator;
        validator->initDataset(filename); 
        
        vector<int> final_features; //array containing all features in best subset
        
        //
        //  accuracy calculations moved to parentSet()
        //
        
        parentSet(tree);
        removeFeature(tree);

        for (int i = 0; i < num_features-1; i++) {
            parentSet(tree);
            removeFeature(tree);
        }
        
        //find maximum overall accuracy and total features eliminated
        for (int i = 0; i < num_features; i++) {
            if (i == 0) {
                max_acc = compare_acc[0];
                eliminated = 1;
            }
            else if(max_acc < compare_acc[i]) {
                max_acc = compare_acc[i];
                eliminated = i + 1;
            }
            
            if (max_acc < default_acc)
                max_acc = default_acc;  
        }
        
        //find all features in best subset
        int valid;
        for (int i = 0; i < num_features; i++) {
            valid = 0;
            
            for (int j = 0; j < eliminated; j++) {
                if(tree->currNode->curr_features.at(j) == feats[i]) {
                    break;
                }
                if(j == eliminated - 1) //checked through all eliminated features
                    valid = 1;
            }
            
            if(valid)
                final_features.push_back(feats.at(i));
        }
        
        //if root/default_acc contains the highest accuracy then reset 'eliminated' counter
        if(max_acc == default_acc)
            eliminated = 0;
        
        if(eliminated == num_features)  //no features would necessary to obtain the highest possible accuracy
            cout << "\n\nFinished search!!! The default rate contains the highest accuracy of " << max_acc << endl;
        else {
            cout << "\n\nFinished search!!! The best feature subset { ";
            for (int i = 0; i < num_features - eliminated; i++)
                cout << final_features[i] << " ";
            cout << "} had an accuracy of " << max_acc << endl;
        }
        
        return;
    }

    void removeFeature(Tree* tree) {
        Node* currNode = tree->currNode;

        //display pre-calculated accuracy within each node of given children
        for (int i = 0; i < num_features - currNode->curr_features.size(); i++) {
            cout << "Accuracy for removing feature {" << new_features.at(i) << "} : " << accuracy[i];
            cout << "\n";
        }
        
        tree->currNode = currNode->children.at(high_node);
        cout << "feature(s) removed: ";
        for (int j = 0; j < tree->currNode->curr_features.size(); j++)
            cout << tree->currNode->curr_features.at(j) << " ";
        cout << "-> resulting in an accuracy of " << compare_acc[compare_cnt2];
        cout << "\n\n";

        compare_cnt2++;
        high_node = 0;
        
        return;
    }

    void parentSet(Tree* tree) {
        int feature_size;
        
        Node* currNode = tree->currNode;
 
        cout << "size: " << num_features - tree->currNode->curr_features.size() << endl;
        feature_size = num_features - tree->currNode->curr_features.size();
        //cout << "Feature size: " << feature_size << endl;
        
        //validator = new Validator;
        vector<int> vfeats = validFeatures(currNode, feature_size);  //temporary vector 
        int cnt5 = 0;   //counter
        
        //begin calculating accuracies for all nodes that will be searched during the greedy search
        if(!drate_valid) {  //occurs only once
            vector<int> dfeats;
            for (int i = 0; i < num_features; i++)
                dfeats.push_back(feats.at(i));
            default_acc = validator->leave_one_out_validation(dfeats, filename, 2);

            cout << "\nInitial accuracy for root { ";
            for(int i=0; i < num_features; i++) {
                cout << feats.at(i) << " ";
            }
            cout << "} : " << default_acc;
            cout << "\n\n";
        
            drate_valid = 1;
        }
        //else {
            for (int i = 0; i < num_features - cnt4; i++) {
                str_vfeat = vfeats.at(cnt5);
                vfeats.erase(vfeats.begin() + cnt5);    //erase each individual features to get the new accuracy
                accuracy[i+cnt1] = validator->leave_one_out_validation(vfeats, filename, 2);
                vfeats.insert(vfeats.begin() + cnt5, str_vfeat);    //restore that previously erased feature
                cnt5++;
            }
            cnt4++;
        //}
        
        if (feature_size != 0) {
            new_features = validFeatures(currNode, feature_size);
            cout << "current parent node: ";
            for (int i = 0; i < feature_size; i++) {
                Node* newNode = new Node(tree->currNode);
                newNode->addFeature(new_features.at(i));
                cout << new_features.at(i) << " ";
                currNode->children.push_back(newNode);   
            }
            cout << "\n";
        }
        
        //acquire all values/accuracies for compare_acc
        for (int i = cnt1; i < (cnt1 + num_features - currNode->curr_features.size()); i++) {  
            if (i == cnt1)
                compare_acc[cnt3] = accuracy[0];    //this will only implement once
            if (compare_acc[cnt3] < accuracy[i]) {
                compare_acc[cnt3] = accuracy[i];    //assignment only the highest accuracy among each set of children     
                high_node = i - cnt1;
            }
            
        }
        cnt1 = cnt2;
        cnt3++;
    }

    vector<int> validFeatures(Node* currNode, int feature_size) {
        vector<int> new_feature;
        vector<int> invalid_feats;
        bool invalid;

        if (feature_size == num_features) {
            for (int i = 0; i < num_features; i++)
                new_feature.push_back(feats.at(i));
        }
        
        else if (feature_size < num_features) {
            
            for (int i = 0; i < (num_features - feature_size); i++) {
                invalid_feats.push_back(currNode->curr_features.at(i));
            }
            
            for (int i = 0; i < num_features; i++) {
                invalid = false;
                
                for (int j = 0; j < (num_features - feature_size); j++) {
                    //j++;
                    if (invalid_feats.at(j) == feats.at(i)) {
                        invalid = true;
                    }
                }
                
                if (!invalid) {
                    new_feature.push_back(feats.at(i));
                }
            }
        }
        return new_feature;
    }
};

#endif