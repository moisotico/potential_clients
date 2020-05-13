#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
using namespace std;

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

    // Constructor
    PotentialClient(string person_id,
        string current_role,
        string country,
        int number_of_recommendations,
        int number_of_connections,
        float probability) {
            person_id = "";
            current_role = "";
            country = "";
            industry = "";
            number_of_recommendations = 0;
            number_of_connections = 0;
            probability = 0.0;
        }

    // Method to get client probability 
    float updateProbability();



    float roleCriteria();
    float countryCriteria();
    float industryCriteria();
    float recomendationCriteria();
    float connectionCriteria();

    //Destructor
    ~PotentialClient() {};

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
    if (probability > 0.08){
        cout << "PersonID: " << person_id << " ";
        cout << "probability: " << probability << "\n";
    }
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
            return role_probability = 0.2;

    // If the words "specialist", "marketing", "" or "assistant"
    // appear reduce probability by a 10%.
    else if ((current_role.find("specialist") != string::npos) ||
        (current_role.find("marketing") != string::npos) ||
        (current_role.find("assistant") != string::npos))
            return role_probability = -0.1;
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
        (country == "Canada")   
    ){
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
 * @brief: Read the input file people.in and check probability  
 */
void readProbabilityInFile(string theFile)
{
    ifstream inFile(theFile);
    
    // vec is a vector that stores PotentialClient instances
    vector<PotentialClient> vec;

    if (inFile.is_open())
    {

        while (inFile.good())
        {
            auto contact = PotentialClient("","","",0,0,0.0);
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
            vec.push_back(contact);
        }
        cout << "File read! \n" << "People evaluated: " << vec.size() << "\n";

        inFile.close();
    }
    else
        cout << "ERROR: Unable to open people.in file! \n";
}


/**
 * @brief: Write the output file people.out   
 */
void writeFile(string theFile)
{

    ofstream outfile(theFile);

    if (outfile.is_open())
    {
        /*
        Write to outfile if criteria meets  
        */
        outfile.close();
    }
    else
        cout << "ERROR: Unable to write people.out file \n";
}

int main()
{
    // TODO: printlines
    cout << "Starting to read the file... \n";

    readProbabilityInFile("./data/people.in");
    
    // TODO: finish writeFile
    //    writeFile("people.out");
}
