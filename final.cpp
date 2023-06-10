#include<iostream>
#include<fstream>
#include<exception>
#include<ctime>


using namespace std;


//Function declaration
void count(string s);
void stats();
void print();
void content_check();

//Variables for Storing Different data

string full_sequence="";
string header_array[750]; 
string header_current = "";

int count_scaffold_genome = 0;
int size_of_current_scaffolding = 0; 
int count_genome_frequency[5]; 
int count_array_scaffolding[750]; 


void count(string s){

    for(int start=0; start < s.length(); start++)
    {
        //Find the character

        if(s[start]=='A'){
            count_genome_frequency[0]+=1;
        }
        else if(s[start]=='C'){
            count_genome_frequency[1]+=1;
        }
        else if(s[start]=='G'){
            count_genome_frequency[2]+=1;
        }
         else if(s[start]=='T'){
            count_genome_frequency[3]+=1;
        }
 //       else if(s[start]=='N'){
 //           count_genome_frequency[4]+=1;
 //       }
    }

}

void stats(){
    

    int min=0, max=0;
    long min_size=0, max_size=0, total_size=0;
    int i=0;

    while(i<=count_scaffold_genome){

        if(count_array_scaffolding[i] > max_size){

            max_size = count_array_scaffolding[i];
            max = i;

        }
        if(min_size==0 || count_array_scaffolding[i] < min_size){

            min_size = count_array_scaffolding[i];
            min = i;

        }
        total_size += count_array_scaffolding[i];
        i++;
    }

    cout<<endl<<"Total Scaffolds =  "<<count_scaffold_genome<<endl;
    cout<<endl<<"The Largest Scaffold is: "<<header_array[max]<<"with length "<<max_size<<endl;
    cout<<endl<<"The Smallest Scaffold is: "<<header_array[min]<<"with length "<<min_size<<endl;
    cout<<endl<<"The Average Scaffold length is  :"<<(total_size/count_scaffold_genome)<<endl<<endl;
}

// Function to print the count of occurrences of each alphabet
void print(){

    cout<<endl<<"Frequency in the genome"<<endl;
    cout<<"A = "<< count_genome_frequency[0]<<endl;
    cout<<"C = "<< count_genome_frequency[1]<<endl;
    cout<<"G = "<< count_genome_frequency[2]<<endl;
    cout<<"T = "<< count_genome_frequency[3]<<endl;
    
}

    // Function to Check the C's and G's content percentage in the whole genome
void content_check(){
    
    double total = 0;

    long c = 0; 
    long g = 0;

    c = count_genome_frequency[1];
    g = count_genome_frequency[2];

    for(int i=0; i<5;i++){
        total += count_genome_frequency[i];
    }
    
    cout<<endl<<"C percent in the genome is "<< (c/total) * 100 << "%";
   
    cout<<endl<<"G percetn in the genome is "<< (g/total) * 100 << "%";
    
}
int main(int argc, char ** argv){
    //Check the arguments size.
    if(argc != 3){

        cout<< endl << "Two Arguments Required"<< endl;
        cout<<"Enter 'Choice', 'File Path'"<<endl;

    }

    else{

        //Getting the choice name and the file name from arguments given.
        char* choice = argv[1];
        char* file_name = argv[2];

        time_t start = time(nullptr);
        try{

            

            string line_read, current_sequence;
            fstream file_pointer;

            file_pointer.open(file_name,ios::in);//Opening the file
            
            while(file_pointer>>line_read){

                //Finding the character > in the line read
                if(line_read[0]== '>'){
                    
                    count_array_scaffolding[count_scaffold_genome] = size_of_current_scaffolding;
                    header_array[count_scaffold_genome] = header_current;


                    header_current = line_read;
                    full_sequence +=  current_sequence;
                    size_of_current_scaffolding = 0;
                    count_scaffold_genome++;
                    current_sequence = "";
                }

                //Reading Content of the Scaffold
                else{

                    current_sequence+=line_read;
                    count(line_read);
                    size_of_current_scaffolding+=line_read.length();
                }

            }

            count_array_scaffolding[count_scaffold_genome] = size_of_current_scaffolding;
            header_array[count_scaffold_genome] = header_current;

        }

        //Catching All Exceptions
        catch(exception e){

            cout<<"Failed"<<endl;

            cout<<e.what()<<endl;

            exit(1);

        }

        if(choice[0] == 'A')
        {
            // Execute A questions
            stats();

        }

        else if(choice[0] == 'B')
        {
            
            // Execute B questions
            print();
        
            content_check();

            time_t end = time(nullptr);
            time_t total = end - start;

            cout<<endl<<endl;
            cout<<"Time taken: "<< total<<" seconds";

        }

        else{

            // Incorrect Choice Entered
            cout<< "Choice correct problem"<<endl;
            
        }
    }
    return 0;
}