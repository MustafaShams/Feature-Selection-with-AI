# CS170_Project_2
### Zachary Hill and Khuaja Shams

The following is a guideline of what is expected when implementing the code and the different scenarios to expect for different inputs:

There will be four .txt files containing datasets to test in the program, your job as a user is to select which .txt file to test, decide how many features will be considered in the leave-one-out validation, and the type of sorting algorithm. The results will reveal the correct tree path for finding the highest accuracy.

First, run the output frame of mainCode.cpp in the open terminal by typing: **./runproject.sh** 

(1)

You will see a message asking you to type the exact name of he text file, without any quotations, you wish to use data from. Keep in mind there are only four datasets to select (cs_170_small26.txt, cs_170_large26.txt, cs_170_small90.txt, cs_170_small90.txt), be sure to type one of these files EXACTLY as shown in the parentheses. Then you press Enter and move forward.

![Intro](/readme_pdfs/Intro.pdf)
(2)

Next input is the number of features to begin the program with and will be placed into the tree where the best feature subset will be revealed. Although both the large and small datasets use a diferent number of features, the highest possible input is 10 features. Note: you can't say exactly which features to use, only the range from 2 to n, where n is the input for # of features. Once the number of features is typed, press ENTER to continue.

(3)

The last input before the actual process is the type of algorithm. There will be a list of three algorithms: 1. Forward Selection. 2. Backward Elimination, 3. Our Special Algorithm. Type '1' or '2' to select the algorithm you wish to run but typing '3' will not provide any output (as of yet). Press ENTER to initiate the feature selection process.
Warning: (1) inputted 1 feature in either dataset in backward elimination or (2) more than 11 features in large dataset for backward elimination will cause the program to fail.

![AlgorithmList](/readme_pdfs/AlgList.pdf)
(4)

The output results will mostly be different based on the type of algorithm elected, backward starts will all features as the root while forward begins with an empty subset. Note: the program was meant to show the time it takes to validate the accuracy for each node but waste too much time when implementing one of the larger datasets. Forward selection will continue down the tree until no child nodes are higher than its parent, making it the best subset and highest accuracy; in contrast, backward elimination continues until it reaches the goal state then it compares all previous parent nodes to determine which had the highest accuracy. The pre-calculated accuracy of each node during the greedy search, the best subset, and highest overall accuracy will be displayed in either case.

![Program](/readme_pdfs/Program.pdf)
(5)
Once the best subset is found, you will be asked whether you wish to continue with another feature selection process. Type 'Y' for yes or 'N' for no, then press ENTER. Yes means you will need to provide three more inputs just as stated above while No means the entire program comes to an end.

![End](/readme_pdfs/End.pdf)
Hope this program shows you the wonders of an AI program (finding the best feature(s) within a huge list) and feel free to try out as many combinations as possible!
