#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <sstream>
#include <fstream>
#include <stack>
#include <cmath>
#include <iomanip>
#include <cstdlib>
using namespace std;
#define LET(_x,_a) typeof(_a) _x(_a)
#define FOR(_i, _a, _n) for(LET(_i, _a); _i < _n; ++_i)
#define REP(_i, _n) FOR(_i, 0, _n)
#define pb push_back
#define sz size()
#define cs c_str()
#define _DEBUG 1
#define _dbg(_x) cout<<#_x<<":"<<(_x)
#define dbg(_x) if(_DEBUG)_dbg(_x), cout<<"\t";
#define dbge(_x) if(_DEBUG)_dbg(_x), cout<<"\n";
#define s2i(_str) ({stringstream sin(_str); int _x; sin>>_x; _x;})
#define s2ull(_str) ({stringstream sin(_str); ULL _x; sin>>_x; _x;})
#define s2d(_str) ({stringstream sin(_str); double _x; sin>>_x; _x;})
#define num2s(_x) ({stringstream sout; sout<<_x; sout.str();})
#define SAFEEXPONENT(_val) ({double _x = 0.0; if(_val < -50)_x = 0.0; else if(_val > 21)_x = INT_MAX; else _x = exp(_val); _x;})
#define SAFESIGMOID(_val) ({double _x = 0.0; if(_val < -21)_x = 0.0; else if(_val > 50)_x = 1.0; else _x = 1.0/(1.0 + exp(-1*_val)); _x;})
#define SAFELOG10DIVIDE(_val, _divide) ({double _x = 0.0; if(_val > 0)_x = log10(_val); if(_divide > EPSILON)_x /= _divide; _x;})
#define NORM(theta, prevtheta) ({double _x = 0.0; REP(_i, numfeatures)_x += (theta[_i] - prevtheta[_i]) * (theta[_i] - prevtheta[_i]); _x = sqrt(_x); _x;})
typedef unsigned long long ULL;
const double EPSILON = 1e-9;
const double CONVERGENCETHRESHOLD = 1e-4;
const double STEPSIZE = 1e-3;
const double REGULARIZATIONCONSTANT = 1e-3;
const int MODELTYPE_LINEAR_REGRESSION = 1;
const int MODELTYPE_LOGISTIC_REGRESSION = 2;
const int PHASE_TRAINING = 1;
const int PHASE_VALIDATION = 2;
const int PHASE_TESTING = 3;
const int PHASE_SUBMISSION = 4;
const int PHASE_SMALLVALIDATION = 5;
const int MAXITERATIONS = 240000000;
const int MAX_NUMBER_OF_FEATURES = 250;
double theta[MAX_NUMBER_OF_FEATURES], features[MAX_NUMBER_OF_FEATURES];
const int MAX_BUFFER_LENGTH = 100000;
char buff[MAX_BUFFER_LENGTH];
const string TRAINING_FILE = "F:\\track2\\training_interactionfeatures.txt";
const string VALIDATION_FILE = "F:\\track2\\validation_interactionfeatures.txt";
const string SMALLVALIDATION_FILE = "F:\\track2\\smallvalidation_interactionfeatures.txt";
const string TESTING_FILE = "F:\\track2\\testing_interactionfeatures.txt";
const string SUBMISSION_FILE = "F:\\track2\\submission_interactionfeatures.txt";
const string OUTPUT_TRAINING_FILE = "F:\\track2\\output_training_logistic_regression.txt";
const string OUTPUT_VALIDATION_FILE = "F:\\track2\\output_validation_logistic_regression.txt";
const string OUTPUT_TESTING_FILE = "F:\\track2\\output_testing_logistic_regression.txt";
const string OUTPUT_SUBMISSION_FILE = "F:\\track2\\output_submission_logistic_regression.txt";
const string OUTPUT_WMAE_FILE = "F:\\track2\\output_wmae_logistic_regression.txt";
const string ADTITLE_TOKENS_FILE = "C:\\Users\\Arvind\\Desktop\\data\\titleid_tokensid.txt";
const string ADDESCRIPTION_TOKENS_FILE = "C:\\Users\\Arvind\\Desktop\\data\\descriptionid_tokensid.txt";
const string KEYWORD_TOKENS_FILE = "C:\\Users\\Arvind\\Desktop\\data\\purchasedkeywordid_tokensid.txt";
const string DISPLAYURL_PROPERTIES_FILE = "C:\\Users\\Arvind\\Desktop\\data\\displayurl_clicks_impressions_uniqueusers.txt";
const string ADVERTISER_PROPERTIES_FILE = "C:\\Users\\Arvind\\Desktop\\data\\advertiser_properties.txt";
const string USER_FEATURES_FILE = "C:\\Users\\Arvind\\Desktop\\data\\userid_profile.txt";
const string TOKENCOUNTS_UNIQUE_QUERIES_FILE = "C:\\Users\\Arvind\\Desktop\\data\\analysis_queryid_tokensid.txt";
const string TOKENCOUNTS_TRAINING_QUERIES_FILE = "C:\\Users\\Arvind\\Desktop\\data\\analysis_training_querytokensid.txt";
const string TOKENCOUNTS_TRAINING_KEYWORDS_FILE = "C:\\Users\\Arvind\\Desktop\\data\\analysis_training_keywordtokensid.txt";
const string TOKENCOUNTS_ADTITLE_FILE = "C:\\Users\\Arvind\\Desktop\\data\\analysis_titleid_tokensid.txt";
const string TOKENCOUNTS_ADDESCRIPTION_FILE = "C:\\Users\\Arvind\\Desktop\\data\\analysis_descriptionid_tokensid.txt";
const string TOKENCOUNTS_KEYWORD_FILE = "C:\\Users\\Arvind\\Desktop\\data\\analysis_purchasedkeywordid_tokensid.txt";
const int MAX_AD_TITLES = 4100000, MAX_AD_DESCRIPTIONS = 3200000, MAX_KEYWORDS = 1300000, MAX_TOKENS = 1300000, MAX_USERS = 25000000;
const int MAX_DISPLAYURLS = 30000, MAX_ADVERTISERS = 40000;
const int MAX_ADTITLE_FEATURES = 21, MAX_ADDESCRIPTION_FEATURES = 25, MAX_DISPLAYURL_FEATURES = 4, MAX_KEYWORD_FEATURES = 30, MAX_ADVERTISER_FEATURES = 6;
double adtitlefeatures[MAX_AD_TITLES][MAX_ADTITLE_FEATURES], addescfeatures[MAX_AD_DESCRIPTIONS][MAX_ADDESCRIPTION_FEATURES], keywordfeatures[MAX_KEYWORDS][MAX_KEYWORD_FEATURES];
double displayurlfeatures[MAX_DISPLAYURLS][MAX_DISPLAYURL_FEATURES], advertiserfeatures[MAX_ADVERTISERS][MAX_ADVERTISER_FEATURES];
const int MAX_TOKEN_TYPES = 6;
double tokencounts[MAX_TOKENS][MAX_TOKEN_TYPES];
const int TOKEN_TYPE_UNIQUE_QUERIES = 0, TOKEN_TYPE_TRAINING_QUERIES = 1, TOKEN_TYPE_TRAINING_KEYWORDS = 2, TOKEN_TYPE_ADTITLE = 3, TOKEN_TYPE_ADDESCRIPTION = 4, TOKEN_TYPE_KEYWORD = 5;
const double DIVIDE_TOKEN_TYPE_UNIQUE_QUERIES = 6.71, DIVIDE_TOKEN_TYPE_TRAINING_QUERIES = 7.13, DIVIDE_TOKEN_TYPE_TRAINING_KEYWORDS = 6.9;
const double DIVIDE_TOKEN_TYPE_ADTITLE = 6.24, DIVIDE_TOKEN_TYPE_ADDESCRIPTION = 6.81, DIVIDE_TOKEN_TYPE_KEYWORD = 4.74;
const double DIVIDE_DISPLAYURL_CLICKS = 5.95, DIVIDE_DISPLAYURL_IMPRESSIONS = 7.38, DIVIDE_DISPLAYURL_UNIQUEUSERS = 6.94;
const double DIVIDE_ADVERTISER_UNIQUEADS = 4.68, DIVIDE_ADVERTISER_UNIQUEADSIMPRESSED = 4.68, DIVIDE_ADVERTISER_TOTALIMPRESSIONS = 7.3, DIVIDE_ADVERTISER_UNIQUEADSCLICKED = 4.13, DIVIDE_ADVERTISER_TOTALCLICKS = 5;
const int FEATUREOFFSET_IMPRESSIONS = 0, FEATUREOFFSET_TARGET = 1, FEATUREOFFSET_DISPLAYURL = 2, FEATUREOFFSET_ADVERTISERID = 3, FEATUREOFFSET_DEPTHFEATURE = 4, FEATUREOFFSET_POSITIONFEATURE = 5, FEATUREOFFSET_KEYWORDID = 6, FEATUREOFFSET_ADTITLEID = 7, FEATUREOFFSET_ADDESCID = 8, FEATUREOFFSET_USERID = 9, FEATUREOFFSET_INTERACTION_START = 10, FEATUREOFFSET_INTERACTION_END = 18, FEATUREOFFSET_QUERYTOKEN_START = 19;
int userfeatures[MAX_USERS][2];
const int MAX_QUERY_TOKENS = 10;
int querytokens[MAX_QUERY_TOKENS];
map<ULL, int> displayurlmap;

char *ptr = NULL, *ptr2 = NULL;
int modeltype = MODELTYPE_LOGISTIC_REGRESSION;
int numfeatures = 0, numuserfeatures = 10, numadtitlefeatures = MAX_ADTITLE_FEATURES, numaddescfeatures = MAX_ADDESCRIPTION_FEATURES, numdisplayurlfeatures = MAX_DISPLAYURL_FEATURES, numkeywordfeatures = MAX_KEYWORD_FEATURES, numadvertiserfeatures = MAX_ADVERTISER_FEATURES;
int numberOfValidationPasses = 0;
vector<int> tokenidvec;
vector<double> tokenidscorevec;
ofstream foutwmae;

void OutputSubmission(string inputfile, string outputfile);

void Initialize()
{
  displayurlmap.clear();
  tokenidvec.clear();
  tokenidscorevec.clear();
  
  memset(tokencounts, 0, sizeof(tokencounts));
  memset(userfeatures, 0, sizeof(userfeatures));
  memset(adtitlefeatures, 0, sizeof(adtitlefeatures));
  memset(addescfeatures, 0, sizeof(addescfeatures));
  memset(keywordfeatures, 0, sizeof(keywordfeatures));
  memset(displayurlfeatures, 0, sizeof(displayurlfeatures));
  memset(advertiserfeatures, 0, sizeof(advertiserfeatures));
  memset(querytokens, 0, sizeof(querytokens));
    
  srand(time(NULL));
  //initialize theta
  REP(i, MAX_NUMBER_OF_FEATURES)theta[i] = rand() / RAND_MAX;
  
  foutwmae.open(OUTPUT_WMAE_FILE.cs);
}

void LoadTokenCounts(string file, int index, double divide)
{
  ifstream fin(file.cs);
  if(!fin){cout<<"Could not open file:"<<file<<endl; exit(0);}
  cout<<"Begin processing:"<<file<<endl;
  int lineno = -1;
 
  int numtokens = 0;
  int tokenid = -1, tokencount = 0;
  
  clock_t start = clock();
  while(fin)
  {
    lineno++;
    if(fin.eof())break;
    fin >> tokenid >> tokencount;
    if(tokenid == -1)continue;

    tokencounts[tokenid][index] = SAFELOG10DIVIDE(tokencount, divide);
    
    if(lineno % 1000000 == 0)cout<<"Time taken to load "<< lineno <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
    if(lineno < 5)
    {
      dbg(tokenid); dbg(tokencount); dbge(tokencounts[tokenid][index]);
    }
    if(tokenid > numtokens)numtokens = tokenid;
  }
  dbge(numtokens);
  cout<<"Time taken to load "<< lineno <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
  fin.close();
}

void LoadUserFeatures(string file)
{
  ifstream fin(file.cs);
  if(!fin){cout<<"Could not open file:"<<file<<endl; exit(0);}
  cout<<"Begin processing:"<<file<<endl;
  int lineno = -1;
 
  int numusers = 0;
  int userid = -1, gender = 0, agebucket = 0;
  
  clock_t start = clock();
  while(fin)
  {
    lineno++;
    if(fin.eof())break;
    fin >> userid >> gender >> agebucket;
    if(userid == -1)continue;

    if(gender != 1 && gender != 2)gender = 0;
    if(agebucket < 1)agebucket = 1;
    if(agebucket > 6)agebucket  = 6;
    
    userfeatures[userid][0] = gender;
    userfeatures[userid][1] = agebucket;
    
    if(lineno % 1000000 == 0)cout<<"Time taken to load "<< lineno <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
    if(lineno < 5)
    {
      dbg(userid); dbg(gender); dbg(userfeatures[userid][0]); dbg(agebucket); dbge(userfeatures[userid][1]);
    }
    if(userid > numusers)numusers = userid;
  }
  dbge(numusers);
  cout<<"Time taken to load "<< lineno <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
  fin.close();
}

void LoadAdTitleFeatures(string file)
{
  ifstream fin(file.cs);
  if(!fin){cout<<"Could not open file:"<<file<<endl; exit(0);}
  cout<<"Begin processing:"<<file<<endl;
  int lineno = -1;
  
  int titleid = -1, lentokenstr = 0;
  string tokenstr = "", str = "";
  int numtokens = 0, numadtitles = 0;
  int minlentokenvector = 0;
  
  clock_t start = clock();
  while(fin)
  {
    lineno++;
    if(fin.eof())break;
    fin >> titleid >> tokenstr;
    if(titleid == -1)continue;
    lentokenstr = tokenstr.sz;
    
    str = "";
    tokenidvec.clear();
    tokenidscorevec.clear();
    
    REP(i, lentokenstr)
    if(tokenstr[i] == '|')tokenidvec.pb( s2i(str) ), str = "";
    else str += tokenstr[i];
    if(str.sz > 0)tokenidvec.pb( s2i(str) );
    
    numtokens = tokenidvec.sz;

    if(numtokens > 25)adtitlefeatures[titleid][5] = 1.0;
    else if(numtokens > 20)adtitlefeatures[titleid][4] = 1.0;
    else if(numtokens > 15)adtitlefeatures[titleid][3] = 1.0;
    else if(numtokens > 10)adtitlefeatures[titleid][2] = 1.0;
    else if(numtokens > 5)adtitlefeatures[titleid][1] = 1.0;
    else adtitlefeatures[titleid][0] = 1.0;
    
    minlentokenvector = numtokens;
    if(minlentokenvector > 10)minlentokenvector = 10;
    //First 6 features are relating to number of words in ad title
    REP(i, minlentokenvector)adtitlefeatures[titleid][6 + i] = tokencounts[ tokenidvec[i] ][TOKEN_TYPE_ADTITLE];
    
    REP(i, numtokens)tokenidscorevec.pb( tokencounts[ tokenidvec[i] ][TOKEN_TYPE_KEYWORD] );
    sort(tokenidscorevec.begin(), tokenidscorevec.end());
    reverse(tokenidscorevec.begin(), tokenidscorevec.end());
    
    if(minlentokenvector > 5)minlentokenvector = 5;
    //Featureids 6-15 are counts of first 10 words in ad title. The below features are counts of top 5 words in ad title from the bidded keyword corpus
    REP(i, minlentokenvector)adtitlefeatures[titleid][16 + i] = tokenidscorevec[i];
    
    if(lineno % 1000000 == 0)cout<<"Time taken to load "<< lineno <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
    if(lineno < 5)
    {
      dbg(titleid); dbge(tokenstr);
      REP(i, numadtitlefeatures)cout<<" "<<adtitlefeatures[ titleid ][i];
      cout<<endl;
    }
    if(titleid > numadtitles)numadtitles = titleid;
  }
  dbge(numadtitles);
  cout<<"Time taken to load "<< lineno <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
  fin.close();
}

void LoadAdDescriptionFeatures(string file)
{
  ifstream fin(file.cs);
  if(!fin){cout<<"Could not open file:"<<file<<endl; exit(0);}
  cout<<"Begin processing:"<<file<<endl;
  int lineno = -1;
  
  int descid = -1, lentokenstr = 0;
  string tokenstr = "", str = "";
  int numtokens = 0, numaddesc = 0;
  int minlentokenvector = 0;
  
  clock_t start = clock();
  while(fin)
  {
    lineno++;
    if(fin.eof())break;
    fin >> descid >> tokenstr;
    if(descid == -1)continue;
    lentokenstr = tokenstr.sz;
    
    str = "";
    tokenidvec.clear();
    tokenidscorevec.clear();
    
    REP(i, lentokenstr)
    if(tokenstr[i] == '|')tokenidvec.pb( s2i(str) ), str = "";
    else str += tokenstr[i];
    if(str.sz > 0)tokenidvec.pb( s2i(str) );
    
    numtokens = tokenidvec.sz;

    if(numtokens > 40)addescfeatures[descid][4] = 1.0;
    else if(numtokens > 30)addescfeatures[descid][3] = 1.0;
    else if(numtokens > 20)addescfeatures[descid][2] = 1.0;
    else if(numtokens > 10)addescfeatures[descid][1] = 1.0;
    else addescfeatures[descid][0] = 1.0;
    
    minlentokenvector = numtokens;
    if(minlentokenvector > 10)minlentokenvector = 10;
    //First 5 features are relating to number of words in ad description
    REP(i, minlentokenvector)addescfeatures[descid][5 + i] = tokencounts[ tokenidvec[i] ][TOKEN_TYPE_ADDESCRIPTION];
    
    REP(i, numtokens)tokenidscorevec.pb( tokencounts[ tokenidvec[i] ][TOKEN_TYPE_KEYWORD] );
    sort(tokenidscorevec.begin(), tokenidscorevec.end());
    reverse(tokenidscorevec.begin(), tokenidscorevec.end());
    
    //Featureids 5-14 are counts of first 10 words in ad description. The below features are counts of top 10 words in ad description from the bidded keyword corpus
    REP(i, minlentokenvector)addescfeatures[descid][15 + i] = tokenidscorevec[i];
    
    if(lineno % 1000000 == 0)cout<<"Time taken to load "<< lineno <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
    if(lineno < 5)
    {
      dbg(descid); dbge(tokenstr);
      REP(i, numaddescfeatures)cout<<" "<<addescfeatures[ descid ][i];
      cout<<endl;
    }
    if(descid > numaddesc)numaddesc = descid;
  }
  dbge(numaddesc);
  cout<<"Time taken to load "<< lineno <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
  fin.close();
}

void LoadDisplayUrlFeatures(string file)
{
  ifstream fin(file.cs);
  if(!fin){cout<<"Could not open file:"<<file<<endl; exit(0);}
  cout<<"Begin processing:"<<file<<endl;
  int lineno = -1;
  
  ULL displayurl = 0LL;
  int clicks = -1, impressions = -1, uniqueusers = -1;
  
  clock_t start = clock();
  while(fin)
  {
    lineno++;
    if(fin.eof())break;
    clicks = -1, impressions = -1, uniqueusers = -1;
    fin >> displayurl >> clicks >> impressions >> uniqueusers;
    if(clicks == -1)continue;
    displayurlmap[displayurl] = lineno;
    displayurlfeatures[lineno][0] = SAFELOG10DIVIDE( clicks, DIVIDE_DISPLAYURL_CLICKS );
    displayurlfeatures[lineno][1] = SAFELOG10DIVIDE( impressions, DIVIDE_DISPLAYURL_IMPRESSIONS );
    displayurlfeatures[lineno][2] = SAFELOG10DIVIDE( uniqueusers, DIVIDE_DISPLAYURL_UNIQUEUSERS );
    if(impressions > 0) displayurlfeatures[lineno][3] = SAFESIGMOID( 5 * clicks / (double)impressions );
        
    if(lineno % 10000 == 0)cout<<"Time taken to load "<< lineno <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
    if(lineno < 5)
    {
      dbg(displayurl); dbg(lineno); dbg(clicks); dbg(impressions); dbge(uniqueusers);
      REP(i, MAX_DISPLAYURL_FEATURES)cout<<" "<<displayurlfeatures[lineno][i];
      cout<<endl;
    }
  }
  cout<<"Time taken to load "<< lineno <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
  fin.close();
}

void LoadKeywordFeatures(string file)
{
  ifstream fin(file.cs);
  if(!fin){cout<<"Could not open file:"<<file<<endl; exit(0);}
  cout<<"Begin processing:"<<file<<endl;
  int lineno = -1;
  
  int keywordid = -1, lentokenstr = 0;
  string tokenstr = "", str = "";
  int numtokens = 0, numkeywords = 0;
  int minlentokenvector = 0;
  
  clock_t start = clock();
  while(fin)
  {
    lineno++;
    if(fin.eof())break;
    fin >> keywordid >> tokenstr;
    if(keywordid == -1)continue;
    lentokenstr = tokenstr.sz;

    str = "";
    tokenidvec.clear();
    
    REP(i, lentokenstr)
    if(tokenstr[i] == '|')tokenidvec.pb( s2i(str) ), str = "";
    else str += tokenstr[i];
    if(str.sz > 0)tokenidvec.pb( s2i(str) );
    
    numtokens = tokenidvec.sz;
    
    minlentokenvector = numtokens;
    if(minlentokenvector > 5)minlentokenvector = 5;
    //First 6 features are relating to number of words in ad title
    REP(tokentype, MAX_TOKEN_TYPES)REP(i, minlentokenvector)keywordfeatures[keywordid][tokentype * 5 + i] = tokencounts[ tokenidvec[i] ][tokentype];
        
    if(lineno % 1000000 == 0)cout<<"Time taken to load "<< lineno <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
    if(lineno < 5)
    {
      dbg(keywordid); dbge(tokenstr); 
      REP(i, MAX_KEYWORD_FEATURES)cout<<" "<<keywordfeatures[keywordid][i];
      cout<<endl;
    }
    if(keywordid > numkeywords)numkeywords = keywordid;
  }
  dbge(numkeywords);
  cout<<"Time taken to load "<< lineno <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
  fin.close();
}

void LoadAdvertiserFeatures(string file)
{
  ifstream fin(file.cs);
  if(!fin){cout<<"Could not open file:"<<file<<endl; exit(0);}
  cout<<"Begin processing:"<<file<<endl;
  int lineno = -1;
  
  int advertiserid = -1, uniqueads = 0, uniqueadsimpressed = 0, totalimpressions = 0, uniqueadsclicked = 0, totalclicks = 0;
  int numadvertisers = 0;
  
  clock_t start = clock();
  while(fin)
  {
    lineno++;
    if(fin.eof())break;
    advertiserid = -1, uniqueads = 0, uniqueadsimpressed = 0, totalimpressions = 0, uniqueadsclicked = 0, totalclicks = 0;
    fin >> advertiserid >> uniqueads >> uniqueadsimpressed >> totalimpressions >> uniqueadsclicked >> totalclicks;
    if(advertiserid == -1)continue;

    advertiserfeatures[advertiserid][0] = SAFELOG10DIVIDE( uniqueads, DIVIDE_ADVERTISER_UNIQUEADS );
    advertiserfeatures[advertiserid][1] = SAFELOG10DIVIDE( uniqueadsimpressed, DIVIDE_ADVERTISER_UNIQUEADSIMPRESSED );
    advertiserfeatures[advertiserid][2] = SAFELOG10DIVIDE( totalimpressions, DIVIDE_ADVERTISER_TOTALIMPRESSIONS );
    advertiserfeatures[advertiserid][3] = SAFELOG10DIVIDE( uniqueadsclicked, DIVIDE_ADVERTISER_UNIQUEADSCLICKED );
    advertiserfeatures[advertiserid][4] = SAFELOG10DIVIDE( totalclicks, DIVIDE_ADVERTISER_TOTALCLICKS );
    if(totalimpressions > 0) advertiserfeatures[advertiserid][5] = SAFESIGMOID( 5 * totalclicks / (double)totalimpressions );
        
    if(lineno % 10000 == 0)cout<<"Time taken to load "<< lineno <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
    if(lineno < 5)
    {
      dbg(advertiserid); dbg(uniqueads); dbg(uniqueadsimpressed); dbg(totalimpressions); dbg(uniqueadsclicked); dbge(totalclicks);
      REP(i, MAX_ADVERTISER_FEATURES)cout<<" "<<advertiserfeatures[advertiserid][i];
      cout<<endl;
    }
    if(advertiserid > numadvertisers)numadvertisers = advertiserid;
  }
  dbge(numadvertisers);
  cout<<"Time taken to load "<< lineno <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
  fin.close();  
}

void DoRegression(string file, int phase, int curiteration)
{
  if(phase == PHASE_SUBMISSION)
  {
    cout<<"DoRegression function is invoked only during the training, validation and testing phases"<<endl;
    cout<<"Invoke OutputSubmission function for the submission phase"<<endl;
    return;
  }
  
  if(phase != PHASE_VALIDATION || numberOfValidationPasses == 0)
    cout<<"File:"<<file<<endl;

  if(phase == PHASE_VALIDATION)numberOfValidationPasses++;
  
  int iteration = -1;
  double wmae = 0.0, rmse = 0.0;
  
  clock_t start = clock();
  
  assert(numuserfeatures > 0 && numadtitlefeatures > 0 && numaddescfeatures > 0 && numdisplayurlfeatures > 0 && numkeywordfeatures > 0 && numadvertiserfeatures > 0);
  int featureoffset = 1 ; //featureoffset of 1 for just the bias term
  int sizeoffeatures = sizeof(features);
  double target = 0;
  int displayurl = -1, advertiserid = -1, keywordid = -1, adtitleid = -1, addescid = -1, userid = -1;
  int querytokenindex = 0;
  if(phase == PHASE_TRAINING)numfeatures = 1 + 11 + MAX_TOKEN_TYPES * MAX_QUERY_TOKENS + numuserfeatures + numadtitlefeatures + numaddescfeatures + numdisplayurlfeatures + numkeywordfeatures + numadvertiserfeatures;
  int columnno = 0, impressions = 0;
  
  while(iteration < MAXITERATIONS)
  {
    ifstream fin(file.cs);
    if(!fin.is_open()){cout<<"Could not open file:"<<file<<endl; exit(1);}
    
    while(!fin.eof())
    {
      iteration++;
      
      memset(features, 0, sizeoffeatures);
      
      fin.getline(buff, MAX_BUFFER_LENGTH);

      //Load target, displayurl, advertiserid, depthfeature, positionfeature, keywordid, adtitleid, addescid, userid
      //query-adtitle features, query-addescription features, query-keyword features, querytokens corresponding to current line
      ptr = ptr2 = buff;
      target = 0;
      displayurl = -1, advertiserid = -1, keywordid = -1, adtitleid = -1, addescid = -1, userid = -1;
      featureoffset = 1;
      features[0] = 1.0; //bias
      querytokenindex = 0;
      
      columnno = 0, impressions = 0;
      while(*ptr)
      {
        if(*ptr == ' ' || *ptr == '\t')
        {
          *ptr = '\0';
          if(columnno == FEATUREOFFSET_IMPRESSIONS)impressions = s2i(ptr2);
          else if(columnno == FEATUREOFFSET_TARGET)target = s2d(ptr2);
          else if(columnno == FEATUREOFFSET_DISPLAYURL)displayurl = s2i(ptr2);
          else if(columnno == FEATUREOFFSET_ADVERTISERID)advertiserid = s2i(ptr2);
          else if(columnno == FEATUREOFFSET_DEPTHFEATURE)features[featureoffset++] = s2d(ptr2);
          else if(columnno == FEATUREOFFSET_POSITIONFEATURE)features[featureoffset++] = s2d(ptr2);
          else if(columnno == FEATUREOFFSET_KEYWORDID)keywordid = s2i(ptr2);
          else if(columnno == FEATUREOFFSET_ADTITLEID)adtitleid = s2i(ptr2);
          else if(columnno == FEATUREOFFSET_ADDESCID)addescid = s2i(ptr2);
          else if(columnno == FEATUREOFFSET_USERID)userid = s2i(ptr2);
          else if(columnno >= FEATUREOFFSET_INTERACTION_START && columnno <= FEATUREOFFSET_INTERACTION_END)features[featureoffset++] = s2d(ptr2);
          else if(columnno >= FEATUREOFFSET_QUERYTOKEN_START)querytokens[querytokenindex++] = s2i(ptr2);
          
          ptr2 = ptr + 1;
          columnno++;
        }
        ptr++; 
      }
      if(displayurl == -1 || advertiserid == -1)continue;
      if(NULL != ptr2 && *ptr2)querytokens[querytokenindex++] = s2i(ptr2);
      
      if(iteration == 0){ dbg(columnno); dbge(featureoffset); }

      //Add Query Level Features
      REP(tokentype, MAX_TOKEN_TYPES)REP(i, querytokenindex)features[featureoffset + tokentype * MAX_QUERY_TOKENS + i] = tokencounts[ querytokens[i] ][tokentype];
      featureoffset += MAX_TOKEN_TYPES * MAX_QUERY_TOKENS;
      //dbge(featureoffset);
      
      //Add User Level Features
      features[ featureoffset + userfeatures[userid][0] ] = 1.0;
      featureoffset += 3;
      features[ featureoffset + userfeatures[userid][1] ] = 1.0;
      featureoffset += 7;
      //dbge(featureoffset);
      
      //Add Ad Title Features
      REP(i, numadtitlefeatures)features[featureoffset++] = adtitlefeatures[adtitleid][i];
      //dbge(featureoffset);
      
      //Add Ad Description features
      REP(i, numaddescfeatures)features[featureoffset++] = addescfeatures[addescid][i];
      //dbge(featureoffset);
      
      //Add DisplayURL features
      REP(i, numdisplayurlfeatures)features[featureoffset++] = displayurlfeatures[displayurl][i];
      //dbge(featureoffset);
      
      //Add Keyword features
      REP(i, numkeywordfeatures)features[featureoffset++] = keywordfeatures[keywordid][i];
      //dbge(featureoffset);
      
      //Add Advertiser features
      REP(i, numadvertiserfeatures)features[featureoffset++] = advertiserfeatures[advertiserid][i];
      //dbg(numfeatures); dbge(featureoffset);
      
      
      //Compute yhat and other required terms for performing gradient descent
      double dotproduct = 0.0, weight = impressions, yhat = 0.0;
      REP(i, numfeatures) dotproduct += theta[i] * features[i];
      if(modeltype == MODELTYPE_LINEAR_REGRESSION)
      {
        yhat = dotproduct;
      }
      else if(modeltype == MODELTYPE_LOGISTIC_REGRESSION)
      {
        yhat = SAFESIGMOID(dotproduct);
        weight *= yhat * (1 - yhat);
      }
      
      if(phase == PHASE_TRAINING) //Do Gradient Descent
      {        
        if(yhat < target - target * EPSILON)
        {
          REP(i, numfeatures)theta[i] = theta[i] - STEPSIZE * (-1 * weight * features[i] + REGULARIZATIONCONSTANT * theta[i]);
        }
        else if(yhat > target + target * EPSILON)
        {
          REP(i, numfeatures)theta[i] = theta[i] - STEPSIZE * (weight * features[i] + REGULARIZATIONCONSTANT * theta[i]);
        }
        else //there is no update the feature because of the weight, because we have perfectly zeroed the loss - this serves as a hack instead of using the subgradient
             //still we need to minimize the regularization term 
        {
          REP(i, numfeatures)theta[i] = theta[i] - STEPSIZE *  REGULARIZATIONCONSTANT * theta[i];
        }
      }
      else if(phase == PHASE_VALIDATION || phase == PHASE_TESTING || phase == PHASE_SMALLVALIDATION)wmae += impressions * abs(yhat - target), rmse += impressions * (yhat - target) * (yhat - target);
      
      if(iteration < 5)
      {
        if(phase != PHASE_SMALLVALIDATION || iteration < 1)
        {
          dbg(iteration); dbg(impressions); dbg(target); dbg(displayurl); dbg(advertiserid); dbg(keywordid); dbg(adtitleid); dbg(addescid); dbge(userid);
          cout<<"Feature Values:";
          REP(i, numfeatures)cout<<" "<<features[i];
          cout<<endl;
          cout<<"Feature Weights:";
          REP(i, numfeatures)cout<<" "<<theta[i];
          cout<<endl;
        }
      }
      
      if(iteration % 1000000 == 0)
        cout<<"Time taken to train "<< iteration <<" iterations is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
      
      // if(iteration % 1000000 == 0 && phase == PHASE_TRAINING)
      // {
        // DoRegression(SMALLVALIDATION_FILE, PHASE_SMALLVALIDATION, iteration);
      // }
    }
    
    fin.close();
    
    if(phase != PHASE_TRAINING)break;
    else  //evaluate performance on the validation set and do another pass over the training file
    {
      DoRegression(VALIDATION_FILE, PHASE_VALIDATION, iteration);
      DoRegression(TESTING_FILE, PHASE_TESTING, iteration);
      OutputSubmission(SUBMISSION_FILE, OUTPUT_SUBMISSION_FILE + num2s(iteration) + ".txt");
      
      if(iteration >= MAXITERATIONS)
      {
        cout<<"Convergence detected after "<<iteration<<" number of iterations over the training set"<<endl;
        cout<<"Feature Weights:";
        REP(i, numfeatures)cout<<" "<<theta[i];
        cout<<endl;
        break;
      }
    }
  }
  
  //output error on validation set and testing sets
  if(phase == PHASE_VALIDATION || phase == PHASE_TESTING || phase == PHASE_SMALLVALIDATION)
  {
    cout<<"file:"<<file<<" curiteration: "<<curiteration<<" wmae:"<<(iteration == 0? 0.0 : wmae / iteration)<<" rmse:"<<(iteration == 0? 0.0 : sqrt(rmse / iteration))<<endl;
    foutwmae<<"file:"<<file<<" curiteration: "<<curiteration<<" wmae:"<<(iteration == 0? 0.0 : wmae / iteration)<<" rmse:"<<(iteration == 0? 0.0 : sqrt(rmse / iteration))<<endl;
  }
}

void OutputSubmission(string inputfile, string outputfile)
{
  ifstream fin(inputfile.cs);
  if(!fin.is_open()){cout<<"Could not open file:"<<inputfile<<endl; exit(1);}
  ofstream fout(outputfile.cs);
  
  int iteration = -1;
  
  clock_t start = clock();
  
  assert(numuserfeatures > 0 && numadtitlefeatures > 0 && numaddescfeatures > 0 && numdisplayurlfeatures > 0 && numkeywordfeatures > 0 && numadvertiserfeatures > 0);
  int featureoffset = 1 ; //featureoffset of 1 for just the bias term
  int sizeoffeatures = sizeof(features);
  double target = 0;
  int displayurl = -1, advertiserid = -1, keywordid = -1, adtitleid = -1, addescid = -1, userid = -1;
  int querytokenindex = 0;
  int columnno = 0, impressions = 0;
  
  while(!fin.eof())
  {
    iteration++;
    
    memset(features, 0, sizeoffeatures);
    
    fin.getline(buff, MAX_BUFFER_LENGTH);

    //Load target, displayurl, advertiserid, depthfeature, positionfeature, keywordid, adtitleid, addescid, userid
    //query-adtitle features, query-addescription features, query-keyword features, querytokens corresponding to current line
    ptr = ptr2 = buff;
    target = 0;
    displayurl = -1, advertiserid = -1, keywordid = -1, adtitleid = -1, addescid = -1, userid = -1;
    featureoffset = 1;
    features[0] = 1.0; //bias
    querytokenindex = 0;
    
    columnno = 0, impressions = 0;
    while(*ptr)
    {
      if(*ptr == ' ' || *ptr == '\t')
      {
        *ptr = '\0';
        if(columnno == FEATUREOFFSET_IMPRESSIONS)impressions = s2i(ptr2);
        else if(columnno == FEATUREOFFSET_TARGET)target = s2d(ptr2);
        else if(columnno == FEATUREOFFSET_DISPLAYURL)displayurl = s2i(ptr2);
        else if(columnno == FEATUREOFFSET_ADVERTISERID)advertiserid = s2i(ptr2);
        else if(columnno == FEATUREOFFSET_DEPTHFEATURE)features[featureoffset++] = s2d(ptr2);
        else if(columnno == FEATUREOFFSET_POSITIONFEATURE)features[featureoffset++] = s2d(ptr2);
        else if(columnno == FEATUREOFFSET_KEYWORDID)keywordid = s2i(ptr2);
        else if(columnno == FEATUREOFFSET_ADTITLEID)adtitleid = s2i(ptr2);
        else if(columnno == FEATUREOFFSET_ADDESCID)addescid = s2i(ptr2);
        else if(columnno == FEATUREOFFSET_USERID)userid = s2i(ptr2);
        else if(columnno >= FEATUREOFFSET_INTERACTION_START && columnno <= FEATUREOFFSET_INTERACTION_END)features[featureoffset++] = s2d(ptr2);
        else if(columnno >= FEATUREOFFSET_QUERYTOKEN_START)querytokens[querytokenindex++] = s2i(ptr2);
        
        ptr2 = ptr + 1;
        columnno++;
      }
      ptr++; 
    }
    if(displayurl == -1 || advertiserid == -1)continue;
    if(NULL != ptr2 && *ptr2)querytokens[querytokenindex++] = s2i(ptr2);
    
    if(iteration == 0){ dbg(columnno); dbge(featureoffset); }

    //Add Query Level Features
    REP(tokentype, MAX_TOKEN_TYPES)REP(i, querytokenindex)features[featureoffset + tokentype * MAX_QUERY_TOKENS + i] = tokencounts[ querytokens[i] ][tokentype];
    featureoffset += MAX_TOKEN_TYPES * MAX_QUERY_TOKENS;
    //dbge(featureoffset);
    
    //Add User Level Features
    features[ featureoffset + userfeatures[userid][0] ] = 1.0;
    featureoffset += 3;
    features[ featureoffset + userfeatures[userid][1] ] = 1.0;
    featureoffset += 7;
    //dbge(featureoffset);
    
    //Add Ad Title Features
    REP(i, numadtitlefeatures)features[featureoffset++] = adtitlefeatures[adtitleid][i];
    //dbge(featureoffset);
    
    //Add Ad Description features
    REP(i, numaddescfeatures)features[featureoffset++] = addescfeatures[addescid][i];
    //dbge(featureoffset);
    
    //Add DisplayURL features
    REP(i, numdisplayurlfeatures)features[featureoffset++] = displayurlfeatures[displayurl][i];
    //dbge(featureoffset);
    
    //Add Keyword features
    REP(i, numkeywordfeatures)features[featureoffset++] = keywordfeatures[keywordid][i];
    //dbge(featureoffset);
    
    //Add Advertiser features
    REP(i, numadvertiserfeatures)features[featureoffset++] = advertiserfeatures[advertiserid][i];
    //dbg(numfeatures); dbge(featureoffset);
    
    
    //Compute yhat and other required terms for performing gradient descent
    double dotproduct = 0.0, yhat = 0.0;
    REP(i, numfeatures) dotproduct += theta[i] * features[i];
    if(modeltype == MODELTYPE_LINEAR_REGRESSION)yhat = dotproduct;
    else if(modeltype == MODELTYPE_LOGISTIC_REGRESSION)yhat = SAFESIGMOID(dotproduct);
    
    double clippedyhat = yhat;
    if(yhat < 0)clippedyhat = 0;
    else if(yhat > 1)clippedyhat = 1;
    
    fout<<clippedyhat<<endl;
    
    if(iteration < 5)
    {
      dbg(iteration); dbg(impressions); dbg(target); dbg(yhat); dbg(clippedyhat); dbg(displayurl); dbg(advertiserid); dbg(keywordid); dbg(adtitleid); dbg(addescid); dbge(userid);
      cout<<"Feature Values:";
      REP(i, numfeatures)cout<<" "<<features[i];
      cout<<endl;
      cout<<"Feature Weights:";
      REP(i, numfeatures)cout<<" "<<theta[i];
      cout<<endl;
    }
    
    if(iteration % 1000000 == 0)
      cout<<"Time taken to output "<< iteration <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
  }
  
  cout<<"Time taken to output "<< iteration <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
  
  fout.close();
  fin.close();
}

int main()
{
  Initialize();

  LoadTokenCounts(TOKENCOUNTS_UNIQUE_QUERIES_FILE, TOKEN_TYPE_UNIQUE_QUERIES, DIVIDE_TOKEN_TYPE_UNIQUE_QUERIES);
  LoadTokenCounts(TOKENCOUNTS_TRAINING_QUERIES_FILE, TOKEN_TYPE_TRAINING_QUERIES, DIVIDE_TOKEN_TYPE_TRAINING_QUERIES);
  LoadTokenCounts(TOKENCOUNTS_TRAINING_KEYWORDS_FILE, TOKEN_TYPE_TRAINING_KEYWORDS, DIVIDE_TOKEN_TYPE_TRAINING_KEYWORDS);    
  LoadTokenCounts(TOKENCOUNTS_ADTITLE_FILE, TOKEN_TYPE_ADTITLE, DIVIDE_TOKEN_TYPE_ADTITLE);
  LoadTokenCounts(TOKENCOUNTS_ADDESCRIPTION_FILE, TOKEN_TYPE_ADDESCRIPTION, DIVIDE_TOKEN_TYPE_ADDESCRIPTION);
  LoadTokenCounts(TOKENCOUNTS_KEYWORD_FILE, TOKEN_TYPE_KEYWORD, DIVIDE_TOKEN_TYPE_KEYWORD);
  LoadUserFeatures(USER_FEATURES_FILE);
  LoadAdTitleFeatures(ADTITLE_TOKENS_FILE);
  LoadAdDescriptionFeatures(ADDESCRIPTION_TOKENS_FILE);
  LoadDisplayUrlFeatures(DISPLAYURL_PROPERTIES_FILE);
  LoadKeywordFeatures(KEYWORD_TOKENS_FILE);
  LoadAdvertiserFeatures(ADVERTISER_PROPERTIES_FILE);
  
  DoRegression(TRAINING_FILE, PHASE_TRAINING, 0);
  // OutputSubmission(SUBMISSION_FILE, OUTPUT_SUBMISSION_FILE);
  OutputSubmission(TESTING_FILE, OUTPUT_TESTING_FILE);
  OutputSubmission(VALIDATION_FILE, OUTPUT_VALIDATION_FILE);
  OutputSubmission(TRAINING_FILE, OUTPUT_TRAINING_FILE);
  

  foutwmae.close();
  return 0;
}
