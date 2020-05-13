#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
#include <utility>
#include <algorithm>

using namespace std;

long unsigned int NUM_TARGET_CUSTOMERS = 100;
// PotentialClient class
class PotentialClient
{

public:
    string person_id;
    string current_role;
    string country;
    string industry;
    int number_of_recommendations;
    int number_of_connections;
    float probability;

    // Method to get client probability 
    float updateProbability();
    float roleCriteria();
    float countryCriteria();
    float industryCriteria();
    float recomendationCriteria();
    float connectionCriteria();

};

/**
 * @brief: Method to get an updated probability.
 * It considers each criteria as an independent variable, also 
 *  it has to  be compared (evaluated and validated) with a real
 *  model to improve the prediction as well as to meassure the error
 */

float PotentialClient::updateProbability(){
    // We asume a base conversion rate of 2/100 
    float base_probability = 0.05;
    probability = base_probability*(1+roleCriteria());
    probability += base_probability*countryCriteria();
    probability += base_probability*industryCriteria();
    probability += base_probability*recomendationCriteria();
    probability += base_probability*connectionCriteria();
    return probability;
}


/**
 * @brief: Method to evaluate the persons current role criteria.
 * This method favors certain words to target the roles of executives,
 * project managers, directors and such that would be interested in  
 * IT Staff Augmentation. 
 */
float PotentialClient::roleCriteria(){
    float role_probability;

    // If the words "president", "chief" or "executive" appear 
    // increase probability by a 30%.
    if ((current_role.find("president") != string::npos) ||
        (current_role.find("chief") != string::npos) ||
        (current_role.find("executive") != string::npos))
            return role_probability = 0.3;

    // If the words "director", "manager" or "project" appear 
    // increase probability by a 20%.        
    else if ((current_role.find("director") != string::npos) ||
        (current_role.find("manager") != string::npos) ||
        (current_role.find("project") != string::npos))
    {
            return role_probability = 0.2;
    }
    // If the words "specialist", "marketing", "" or "assistant"
    // appear reduce probability by a 10%.
    else if ((current_role.find("specialist") != string::npos) ||
        (current_role.find("marketing") != string::npos) ||
        (current_role.find("assistant") != string::npos))
    {
            return role_probability = -0.1;
    }
    else
        return role_probability = 0.0;

}


/**
 * @brief: Method to evaluate the persons current country of residence.
 * This method favors countries of the G7, considering that these are the 
 * seven largest advanced economies in the world based on the 
 *  International Monetary Fund criteria.
 */
float PotentialClient::countryCriteria(){
    float country_probability;
    if ( (country == "United States") ||
        (country == "United Kingdom") ||
        (country == "Japan") ||
        (country == "Italy") ||
        (country == "Germany") ||
        (country == "France") ||
        (country == "Canada"))
    {
        return country_probability = 0.3;
    }
    else
        return country_probability = 0.0;
}


/**
 * @brief: Method to evaluate the persons work industry.
 * This method favors the most digitally advanced sectors, based on 
 *  the Harvard Bussiness review criteria:
 *  https://hbr.org/2016/04/a-chart-that-shows-which-industries-are-the-most-digital-and-why
 */
float PotentialClient::industryCriteria(){
    float industry_probability;
    if ((industry.find("Telecommunications") != string::npos ) ||
        (industry.find("Information") != string::npos ) ||
        (industry.find("Technology") != string::npos ) ||
        (industry.find("Software") != string::npos ) ||
        (industry.find("Engineering") != string::npos ) ||
        (industry.find("Electronics") != string::npos ))
            return industry_probability = 0.3;
        
    else if ((industry.find("Media") != string::npos ) ||
        (industry.find("Marketing") != string::npos ) ||
        (industry.find("Logistics") != string::npos ) ||
        (industry.find("Consulting") != string::npos ) ||
        (industry.find("Insurance") != string::npos ) ||
        (industry.find("Finance") != string::npos )) 
            return industry_probability = 0.2;

    else if ((industry.find("Oil") != string::npos ) ||
        (industry.find("Transportation") != string::npos ) ||
        (industry.find("Real Estate") != string::npos ) ||
        (industry.find("Manufacturing") != string::npos ))
            return industry_probability = 0.1;
    else 
        return industry_probability = 0.0;
}


/**
 * @brief: Method to evaluate the persons LindekIn recomedations.
 * This method favors recomendations of more than five, and ten afterwards
 */
float PotentialClient::recomendationCriteria(){
    float recomendation_probability;

    if (number_of_recommendations >= 10)
        return recomendation_probability = 0.10;
    else if (number_of_recommendations >= 5)
        return recomendation_probability = 0.05;
    else   
        return recomendation_probability = 0.0;
        
}


/**
 * @brief: Method to evaluate the persons LindekIn contacts.
 * This method favors users that have  a number of contacts 
 * over the average (400).
 */
float PotentialClient::connectionCriteria(){
    float connection_probability;
    if (number_of_connections >= 400)
        return connection_probability = 0.2;
    else   
        return connection_probability = 0.0;
        
}


/**
 * @brief Read the input file people.in and check probability  
 */
void readProbabilityInFile(string input_name, vector< pair <string, float> > &vec)
{
    ifstream inFile(input_name);

    if (inFile.is_open())
    {

        while (inFile.good())
        {
            auto contact = PotentialClient();
            string str;
            string::size_type sz;

            //read elements and add them to contact instance
            getline(inFile, contact.person_id, '|');

            //Skip name & last name
            getline(inFile, str, '|');
            getline(inFile, str, '|');

            getline(inFile, contact.current_role, '|');
            getline(inFile, contact.country, '|');
            getline(inFile, contact.industry, '|');
            getline(inFile, str, '|');
            if (!str.empty())
                contact.number_of_connections = stoi(str, nullptr);
            getline(inFile, str, '\n');
            if (!str.empty())
                contact.number_of_connections = stoi(str, nullptr);
            contact.updateProbability();
            vec.push_back(make_pair(contact.person_id, contact.probability));
        }

        inFile.close();
        cout << "File read! \n" << "People evaluated: " << vec.size() << "\n";
    }
    else
        cout << "ERROR: Unable to open "<< input_name << " file \n";;
}


/**
 * @brief: Sorting criteria for the vector pairs   
 */
bool sortBySecDesc(const pair<string,float> &a, 
                   const pair<string,float> &b) 
{ 
       return a.second>b.second; 
} 


/**
 * @brief: Write the output file people.out with the highest k elements   
 */
void writeFile(int k, string outputName,  vector< pair <string, float> > &vec){
    ofstream outfile(outputName);
    int i = 0;
    if (outfile.is_open()){
        for ( auto it = vec.begin(); i < k; it++, i++){
            outfile << it->first << "\n";
        }
        outfile.close();
    }
    else
        cout << "ERROR: Unable to write "<< outputName << " file \n";
}


int main()
{
    // vec is a vector of pair with the person_id and its probability
    vector< pair <string, float> > vec;

    cout << "Starting to read the file... \n";
    readProbabilityInFile("./data/people.in", vec);

    //sort the vector of pairs in descending order
    sort(vec.begin(), vec.end(), sortBySecDesc);
    
    //check the file size
    long unsigned int customers_lenght = NUM_TARGET_CUSTOMERS;
    if( vec.size() < NUM_TARGET_CUSTOMERS){
        customers_lenght = vec.size();
    }
    cout << "Starting to write the .out file... \n";
    writeFile(customers_lenght, "./data/people.out", vec);
}
