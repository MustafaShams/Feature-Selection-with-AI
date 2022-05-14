#ifndef CLASSIFIER_H_
#define CLASSIFIER_H_

//#include <bits/stdc++.h>
#include <vector>
#include <ctime>
#include <time.h>
#include "Dataset.h"

class Classifier
{
public:
	Dataset* training_data;
	int feature_size;
	vector<int> feature_indexes;

	void Train(Dataset* data, vector<int> &features) {
	    training_data = data;
	    feature_size = features.size();
        feature_indexes = features;
		//outputs: None
				//NN classifier isn't a real ML classifier so there is no model for the Train method to build using (train_instances, train_labels) and return.
				//I am guessing that's why the professor said there is no output for this method in the part 2 google doc.

	}

	int Test(int testing_instance)
	{
	    int predicted_label;
	    double distance, shortest_class;
	    double shortest_distance = 1000;
	    double data[1][feature_size + 1];

	    for (int i = 0; i < feature_size; i++)
            data[0][i] = training_data->data[testing_instance][feature_indexes.at(i)];

        for (int i = 0; i < training_data->data_size; i++) {
            distance = 0;
            if (i == testing_instance)
                continue;
            for (int j = 0; j < feature_size; j++)
                distance += pow(data[0][j] - training_data->data[i][feature_indexes.at(j)], 2);
            distance = sqrt(distance);
            if (distance < shortest_distance && i) {
                shortest_distance = distance;
                shortest_class = training_data->data[i][0];
            }
            //cout << training_data->data[i][0]<< ":" << distance << endl;
        }

        predicted_label = shortest_class;
//        cout << "\nShortest distance: " << shortest_distance << endl;
		return predicted_label;
	}
};

#endif