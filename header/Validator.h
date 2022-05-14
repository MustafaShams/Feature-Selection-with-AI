#ifndef VALIDATOR_H_
#define VALIDATOR_H_

//#include <bits/stdc++.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include <chrono>   //required for auto time
#include "Classifier.h"
using namespace std;
using namespace std::chrono;

class Validator {
    public:
        float accuracy_scr = 0.0; //total accuracy score using feature from feat_subset
        int num_lines = 0;  //number of rows with the given text file
        string line;
        int label;
        Dataset* parse;

    void initDataset(string file_choice) {
        parse = new Dataset();
        parse->RowsandColumns(file_choice);
        parse->Parser(file_choice);
    }

    double initRootAccuracy() {
        return parse->defaultRate();
    }

    double leave_one_out_validation (vector<int> subset, string file_choice, int algorithm) {
        int feat_subset[subset.size()]; //subset containing all features currently working with
        int correct_predict_cnt;    //keep track of all correct predictions
        ifstream myfile(file_choice);   //open file; read from the appropriate file

        //transfer all inputted features into feat_subset
        for(int i = 0; i < subset.size(); i++) {
            feat_subset[i] = subset[i];
        }

        //read all instance IDs
        vector<double> instance_ID;
        //read all ground_truth_labels
        vector<double> ground_truth_label;
        
//        Dataset* parse = new Dataset();
//
//        parse->RowsandColumns(file_choice);
//        parse->Parser(file_choice);
        
//        cout << "Columns: " << parse->cols << endl;
//        cout << "Rows: " << parse->rows << endl;
        
        for(int i = 0; i < parse->rows; i++) 
            ground_truth_label.push_back(parse->data[i][0]);  
        
        for(int i = 0; i < parse->rows; i++) 
            for(int j = 1; j < parse->cols; j++)
                instance_ID.push_back(parse->data[i][j]);
        
        correct_predict_cnt = 0;
        double test_instance_ID[parse->rows * (parse->cols - 1)];
        double train_instances[parse->rows * (parse->cols - 1)];
        double predict = 0;
        
        int cnt = 0;
        int cnt2 = 0, cnt3 = 0;
        int overall_cnt = 0;

        Classifier* classifier = new Classifier;
        classifier->Train(parse, subset);
                
        //timer start
//	    printf("\n\nStarting validation...\n");
	    //auto start = high_resolution_clock::now();

       
        for(int i = 0; i < parse->rows; i++) {
            if((feat_subset[cnt]-1) == i){
                for(int j = overall_cnt; j < ((parse->cols - 1) + overall_cnt); j++) {
                    test_instance_ID[cnt2] = instance_ID[j];
                    cnt2++;
                    train_instances[cnt3] = 0;
                    cnt3++;
                    
                }
                cnt++;
                
            }
            
            else {
                for(int j = overall_cnt; j < ((parse->cols - 1) + overall_cnt); j++) {
                    test_instance_ID[cnt2] = 0;
                    cnt2++;
                    train_instances[cnt3] = instance_ID[j];
                    cnt3++;

                }
            }
            
            overall_cnt += (parse->cols - 1);
            
            predict = classifier->Test(i);
                
                    if(predict == ground_truth_label[i]) {
                        correct_predict_cnt++;
                    }
        }
        //timer stop
        //auto stop = high_resolution_clock::now();
        
        //auto duration = duration_cast<microseconds>(stop - start);
	    //cout << "Time taken for validation = " << duration.count() << " ms\n";
		
//        cout << "\n\nCorrect: " << correct_predict_cnt << endl;
        
        accuracy_scr  = correct_predict_cnt / (double)parse->data_size;
//	cout << "\nUsing features { ";
//        for(int i = 0; i < subset.size(); i++)
//            cout << feat_subset[i] << " ";
//        cout << "}, we get accuracy " << accuracy_scr << endl;
      
        return accuracy_scr;
    }

};
#endif
