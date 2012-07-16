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
#define SAFEEXPONENT(_val) ({double _x = 0.0; if(_val < -50)_x = 0.0; else if(_val > 21)_x = INT_MAX; else _x = exp(_val); _x;})
#define SAFESIGMOID(_val) ({double _x = 0.0; if(_val < -21)_x = 0.0; else if(_val > 50)_x = 1.0; else _x = 1.0/(1.0 + exp(-1*_val)); _x;})
#define NORM(theta, prevtheta) ({double _x = 0.0; REP(_i, numfeatures)_x += (theta[_i] - prevtheta[_i]) * (theta[_i] - prevtheta[_i]); _x = sqrt(_x); _x;})
typedef unsigned long long ULL;
const int MAX_QUERIES = 27000000, MAX_AD_TITLES = 4100000, MAX_AD_DESCRIPTIONS = 3200000, MAX_KEYWORDS = 1300000;
int *querytokenids[MAX_QUERIES], *adtitletokenids[MAX_AD_TITLES], *addesctokenids[MAX_AD_DESCRIPTIONS], *keywordtokenids[MAX_KEYWORDS];
const int MAX_BUFFER_LENGTH = 100000;
char buff[MAX_BUFFER_LENGTH];
const string TRAINING_FILE = "F:\\track2\\training.txt";
const string VALIDATION_FILE = "F:\\track2\\validation.txt";
const string TESTING_FILE = "F:\\track2\\testing.txt";
const string SUBMISSION_FILE = "F:\\track2\\submission.txt";
const string OUTPUT_TRAINING_FILE = "F:\\track2\\training_interactionfeatures.txt";
const string OUTPUT_VALIDATION_FILE = "F:\\track2\\validation_interactionfeatures.txt";
const string OUTPUT_TESTING_FILE = "F:\\track2\\testing_interactionfeatures.txt";
const string OUTPUT_SUBMISSION_FILE = "F:\\track2\\submission_interactionfeatures.txt";
const string QUERY_TOKENS_FILE = "C:\\Users\\Arvind\\Desktop\\data\\queryid_tokensid.txt";
const string ADTITLE_TOKENS_FILE = "C:\\Users\\Arvind\\Desktop\\data\\titleid_tokensid.txt";
const string ADDESCRIPTION_TOKENS_FILE = "C:\\Users\\Arvind\\Desktop\\data\\descriptionid_tokensid.txt";
const string KEYWORD_TOKENS_FILE = "C:\\Users\\Arvind\\Desktop\\data\\purchasedkeywordid_tokensid.txt";
const string DISPLAYURL_PROPERTIES_FILE = "C:\\Users\\Arvind\\Desktop\\data\\displayurl_clicks_impressions_uniqueusers.txt";
char *ptr = NULL, *ptr2 = NULL;
int numqueries = 0, numadtitles = 0, numaddesc = 0, numkeywords = 0;
const int FEATURE_QUERYID_OFFSET = 5, FEATURE_KEYWORDID_OFFSET = 6, FEATURE_ADTITLEID_OFFSET = 7, FEATURE_ADDESCRIPTIONID_OFFSET = 8;
const int FEATURE_CLICKS_OFFSET = -2, FEATURE_IMPRESSIONS_OFFSET = -1, FEATURE_DISPLAYURL_OFFSET = 0, FEATURE_ADVERTISERID_OFFSET = 2;
const int FEATURE_DEPTH_OFFSET = 3, FEATURE_POSITION_OFFSET  = 4, FEATURE_USERID_OFFSET = 9;
const double MAX_AD_DEPTH = 3.0;
map<ULL, int> displayurlmap;

void Initialize()
{
  displayurlmap.clear();
  REP(i, MAX_QUERIES)querytokenids[i] = new int[1], querytokenids[0] = 0;
  REP(i, MAX_AD_TITLES)adtitletokenids[i] = new int[1], adtitletokenids[0] = 0;
  REP(i, MAX_AD_DESCRIPTIONS)addesctokenids[i] = new int[1], addesctokenids[0] = 0;
  REP(i, MAX_KEYWORDS)keywordtokenids[i] = new int[1], keywordtokenids[0] = 0;
}

void LoadQueryTokenMapping(string file)
{
  ifstream fin(file.cs);
  if(!fin){cout<<"Could not open file:"<<file<<endl; exit(0);}
  cout<<"Begin processing:"<<file<<endl;
  int lineno = -1;
  
  int queryid = -1, lentokenstr = 0;
  string tokenstr = "", str = "";
  int numtokens = 1;
  
  clock_t start = clock();
  while(fin)
  {
    lineno++;
    if(fin.eof())break;
    fin >> queryid >> tokenstr;
    if(queryid == -1)continue;
    lentokenstr = tokenstr.sz;
    
    str = "";
    numtokens = 1; //numtokens is one more than number of "|"
    REP(i, lentokenstr)if(tokenstr[i] == '|')numtokens++;
    
    querytokenids[queryid] = new int[numtokens + 1];
    querytokenids[queryid][0] = numtokens;
    
    numtokens = 1;
    REP(i, lentokenstr)
    if(tokenstr[i] == '|')querytokenids[queryid][numtokens++] = s2i(str), str = "";
    else str += tokenstr[i];
    
    if(str.sz > 0)querytokenids[queryid][numtokens] = s2i(str);
    
    if(lineno % 1000000 == 0)cout<<"Time taken to load "<< lineno <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
    if(lineno < 5)
    {
      dbg(queryid); dbg(tokenstr); dbge(querytokenids[queryid][0]);
      FOR(i, 1, querytokenids[queryid][0] + 1)cout<<" "<<querytokenids[queryid][i];
      cout<<endl;
    }
    if(queryid > numqueries)numqueries = queryid;
  }
  dbge(numqueries);
  cout<<"Time taken to load "<< lineno <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
  fin.close();
}

void LoadAdTitleTokenMapping(string file)
{
  ifstream fin(file.cs);
  if(!fin){cout<<"Could not open file:"<<file<<endl; exit(0);}
  cout<<"Begin processing:"<<file<<endl;
  int lineno = -1;
  
  int titleid = -1, lentokenstr = 0;
  string tokenstr = "", str = "";
  int numtokens = 1;
  
  clock_t start = clock();
  while(fin)
  {
    lineno++;
    if(fin.eof())break;
    fin >> titleid >> tokenstr;
    if(titleid == -1)continue;
    lentokenstr = tokenstr.sz;
    
    str = "";
    numtokens = 1; //numtokens is one more than number of "|"
    REP(i, lentokenstr)if(tokenstr[i] == '|')numtokens++;
    
    adtitletokenids[titleid] = new int[numtokens + 1];
    adtitletokenids[titleid][0] = numtokens;
    
    numtokens = 1;
    REP(i, lentokenstr)
    if(tokenstr[i] == '|')adtitletokenids[titleid][numtokens++] = s2i(str), str = "";
    else str += tokenstr[i];
    if(str.sz > 0)adtitletokenids[titleid][numtokens] = s2i(str);
    
    sort(adtitletokenids[titleid] + 1, adtitletokenids[titleid] + adtitletokenids[titleid][0] + 1);
    
    if(lineno % 1000000 == 0)cout<<"Time taken to load "<< lineno <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
    if(lineno < 5)
    {
      dbg(titleid); dbg(tokenstr); dbge(adtitletokenids[titleid][0]);
      FOR(i, 1, adtitletokenids[titleid][0] + 1)cout<<" "<<adtitletokenids[titleid][i];
      cout<<endl;
    }
    if(titleid > numadtitles)numadtitles = titleid;
  }
  dbge(numadtitles);
  cout<<"Time taken to load "<< lineno <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
  fin.close();
}

void LoadAdDescriptionTokenMapping(string file)
{
  ifstream fin(file.cs);
  if(!fin){cout<<"Could not open file:"<<file<<endl; exit(0);}
  cout<<"Begin processing:"<<file<<endl;
  int lineno = -1;
  
  int descid = -1, lentokenstr = 0;
  string tokenstr = "", str = "";
  int numtokens = 1;
  
  clock_t start = clock();
  while(fin)
  {
    lineno++;
    if(fin.eof())break;
    fin >> descid >> tokenstr;
    if(descid == -1)continue;
    lentokenstr = tokenstr.sz;
    
    str = "";
    numtokens = 1; //numtokens is one more than number of "|"
    REP(i, lentokenstr)if(tokenstr[i] == '|')numtokens++;
    
    addesctokenids[descid] = new int[numtokens + 1];
    addesctokenids[descid][0] = numtokens;
    
    numtokens = 1;
    REP(i, lentokenstr)
    if(tokenstr[i] == '|')addesctokenids[descid][numtokens++] = s2i(str), str = "";
    else str += tokenstr[i];
    if(str.sz > 0)addesctokenids[descid][numtokens] = s2i(str);
    
    sort(addesctokenids[descid] + 1, addesctokenids[descid] + addesctokenids[descid][0] + 1);    
    
    if(lineno % 1000000 == 0)cout<<"Time taken to load "<< lineno <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
    if(lineno < 5)
    {
      dbg(descid); dbg(tokenstr); dbge(addesctokenids[descid][0]);
      FOR(i, 1, addesctokenids[descid][0] + 1)cout<<" "<<addesctokenids[descid][i];
      cout<<endl;
    }
    if(descid > numaddesc)numaddesc = descid;
  }
  dbge(numaddesc);
  cout<<"Time taken to load "<< lineno <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
  fin.close();
}

void LoadKeywordTokenMapping(string file)
{
  ifstream fin(file.cs);
  if(!fin){cout<<"Could not open file:"<<file<<endl; exit(0);}
  cout<<"Begin processing:"<<file<<endl;
  int lineno = -1;
  
  int keywordid = -1, lentokenstr = 0;
  string tokenstr = "", str = "";
  int numtokens = 1;
  
  clock_t start = clock();
  while(fin)
  {
    lineno++;
    if(fin.eof())break;
    fin >> keywordid >> tokenstr;
    if(keywordid == -1)continue;
    lentokenstr = tokenstr.sz;
    
    str = "";
    numtokens = 1; //numtokens is one more than number of "|"
    REP(i, lentokenstr)if(tokenstr[i] == '|')numtokens++;
    
    keywordtokenids[keywordid] = new int[numtokens + 1];
    keywordtokenids[keywordid][0] = numtokens;
    
    numtokens = 1;
    REP(i, lentokenstr)
    if(tokenstr[i] == '|')keywordtokenids[keywordid][numtokens++] = s2i(str), str = "";
    else str += tokenstr[i];
   
    if(str.sz > 0)keywordtokenids[keywordid][numtokens] = s2i(str);

    sort(keywordtokenids[keywordid] + 1, keywordtokenids[keywordid] + keywordtokenids[keywordid][0] + 1);
    
    if(lineno % 1000000 == 0)cout<<"Time taken to load "<< lineno <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
    if(lineno < 5)
    {
      dbg(keywordid); dbg(tokenstr); dbge(keywordtokenids[keywordid][0]);
      FOR(i, 1, keywordtokenids[keywordid][0] + 1)cout<<" "<<keywordtokenids[keywordid][i];
      cout<<endl;
    }
    if(keywordid > numkeywords)numkeywords = keywordid;
  }
  dbge(numkeywords);
  cout<<"Time taken to load "<< lineno <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
  fin.close();
}

void LoadDisplayUrlMapping(string file)
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
        
    if(lineno % 10000 == 0)cout<<"Time taken to load "<< lineno <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
    if(lineno < 5)
    {
      dbg(displayurl); dbg(clicks); dbg(impressions); dbge(uniqueusers);
    }
  }
  cout<<"Time taken to load "<< lineno <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
  fin.close();
}

void ComputeInteractionFeatures(string inputfile, string outputfile, int startFeatureOffset)
{
  ifstream fin(inputfile.cs);
  if(!fin){cout<<"Could not open file:"<<inputfile<<endl; exit(0);}
  cout<<"Begin processing:"<<inputfile<<endl;
  int lineno = -1;
  
  ofstream fout(outputfile.cs);
  
  int keywordid = -1, adtitleid = -1, addescid = -1, queryid = -1, userid = -1;
  int totalunigrams = 0, minlenquerytokens = 0;
  double dbltotalunigrams = 0.0;
  int numunigrams_matched_title = 0, numunigrams_matched_desc = 0, numunigrams_matched_keyword = 0;
  int numbigrams_matched_title = 0, numbigrams_matched_desc = 0, numbigrams_matched_keyword = 0;
  int numtrigrams_matched_title = 0, numtrigrams_matched_desc = 0, numtrigrams_matched_keyword = 0;
  bool isPreviousUnigramMatchedTitle = false, isPreviousBigramMatchedTitle = false;
  bool isPreviousUnigramMatchedDesc = false, isPreviousBigramMatchedDesc = false;
  bool isPreviousUnigramMatchedKeyword = false, isPreviousBigramMatchedKeyword = false;
  double percentageUnigramsMatchedTitle = 0.0, percentageBigramsMatchedTitle = 0.0, percentageTrigramsMatchedTitle = 0.0;
  double percentageUnigramsMatchedDesc = 0.0, percentageBigramsMatchedDesc = 0.0, percentageTrigramsMatchedDesc = 0.0;
  double percentageUnigramsMatchedKeyword = 0.0, percentageBigramsMatchedKeyword = 0.0, percentageTrigramsMatchedKeyword = 0.0;
  int columnno = 0, clicks = 0, impressions = 0, advertiserid = 0, depth = 0, position = 0;
  double target = 0.0, depthfeature = 0.0, positionfeature = 0.0;
  ULL displayurl = 0ULL;
  
  clock_t start = clock();
  while(fin)
  {
    lineno++;
    if(fin.eof())break;
    fin.getline(buff, MAX_BUFFER_LENGTH);
      
    //Load userid, itemid, rating, timestamp and features corresponding to current line
    ptr = ptr2 = buff;
    keywordid = -1, adtitleid = -1, addescid = -1, queryid = -1, userid = -1;
    
    columnno = 0, clicks = 0, impressions = 0, advertiserid = 0, depth = 0, position = 0;
    displayurl = 0ULL;
    while(*ptr)
    {
      if(*ptr == ' ' || *ptr == '\t')
      {
        *ptr = '\0';
        if(startFeatureOffset > 0 && columnno == startFeatureOffset + FEATURE_CLICKS_OFFSET)clicks = s2i(ptr2);
        else if(startFeatureOffset > 0 && columnno == startFeatureOffset + FEATURE_IMPRESSIONS_OFFSET)impressions = s2i(ptr2);
        else if(columnno == startFeatureOffset + FEATURE_DISPLAYURL_OFFSET)displayurl = s2ull(ptr2);
        else if(columnno == startFeatureOffset + FEATURE_ADVERTISERID_OFFSET)advertiserid = s2i(ptr2);
        else if(columnno == startFeatureOffset + FEATURE_DEPTH_OFFSET)depth = s2i(ptr2);
        else if(columnno == startFeatureOffset + FEATURE_POSITION_OFFSET)position = s2i(ptr2);
        else if(columnno == startFeatureOffset + FEATURE_QUERYID_OFFSET)queryid = s2i(ptr2);
        else if(columnno == startFeatureOffset + FEATURE_KEYWORDID_OFFSET)keywordid = s2i(ptr2);
        else if(columnno == startFeatureOffset + FEATURE_ADTITLEID_OFFSET)adtitleid = s2i(ptr2);
        else if(columnno == startFeatureOffset + FEATURE_ADDESCRIPTIONID_OFFSET)addescid = s2i(ptr2);
        else if(columnno == startFeatureOffset + FEATURE_USERID_OFFSET)userid = s2i(ptr2);
        
        ptr2 = ptr + 1;
        columnno++;
      }
      ptr++; 
    }
    if(queryid == -1)continue;
    if(NULL != ptr2 && *ptr2 && columnno == startFeatureOffset + FEATURE_USERID_OFFSET)userid = s2i(ptr2);
        
    //Compute Interaction Features
    numunigrams_matched_title = 0, numunigrams_matched_desc = 0, numunigrams_matched_keyword = 0;
    numbigrams_matched_title = 0, numbigrams_matched_desc = 0, numbigrams_matched_keyword = 0;
    numtrigrams_matched_title = 0, numtrigrams_matched_desc = 0, numtrigrams_matched_keyword = 0;
    isPreviousUnigramMatchedTitle = false, isPreviousBigramMatchedTitle = false;
    isPreviousUnigramMatchedDesc = false, isPreviousBigramMatchedDesc = false;
    isPreviousUnigramMatchedKeyword = false, isPreviousBigramMatchedKeyword = false;
    totalunigrams = querytokenids[queryid][0];
    dbltotalunigrams = (double)totalunigrams;
    
    FOR(i, 1, totalunigrams + 1)
    {
      if(adtitletokenids[adtitleid][0] > 0 && binary_search(adtitletokenids[adtitleid] + 1, adtitletokenids[adtitleid] + adtitletokenids[adtitleid][0] + 2, querytokenids[queryid][i]))
      {
        numunigrams_matched_title++;
        if(isPreviousBigramMatchedTitle)numtrigrams_matched_title++;
        if(isPreviousUnigramMatchedTitle)numbigrams_matched_title++, isPreviousBigramMatchedTitle = true;
        isPreviousUnigramMatchedTitle = true;
      }
      else isPreviousUnigramMatchedTitle = isPreviousBigramMatchedTitle = false;

      if(addesctokenids[addescid][0] > 0 && binary_search(addesctokenids[addescid] + 1, addesctokenids[addescid] + addesctokenids[addescid][0] + 2, querytokenids[queryid][i]))
      {
        numunigrams_matched_desc++;
        if(isPreviousBigramMatchedDesc)numtrigrams_matched_desc++;
        if(isPreviousUnigramMatchedDesc)numbigrams_matched_desc++, isPreviousBigramMatchedDesc = true;
        isPreviousUnigramMatchedDesc = true;
      }
      else isPreviousUnigramMatchedDesc = isPreviousBigramMatchedDesc = false;

      if(keywordtokenids[keywordid][0] > 0 && binary_search(keywordtokenids[keywordid] + 1, keywordtokenids[keywordid] + keywordtokenids[keywordid][0] + 2, querytokenids[queryid][i]))
      {
        numunigrams_matched_keyword++;
        if(isPreviousBigramMatchedKeyword)numtrigrams_matched_keyword++;
        if(isPreviousUnigramMatchedKeyword)numbigrams_matched_keyword++, isPreviousBigramMatchedKeyword = true;
        isPreviousUnigramMatchedKeyword = true;
      }
      else isPreviousUnigramMatchedKeyword = isPreviousBigramMatchedKeyword = false;
      
    }
    
    percentageUnigramsMatchedTitle = 0.0, percentageBigramsMatchedTitle = 0.0, percentageTrigramsMatchedTitle = 0.0;
    percentageUnigramsMatchedDesc = 0.0, percentageBigramsMatchedDesc = 0.0, percentageTrigramsMatchedDesc = 0.0;
    percentageUnigramsMatchedKeyword = 0.0, percentageBigramsMatchedKeyword = 0.0, percentageTrigramsMatchedKeyword = 0.0;
    
    if(totalunigrams > 0)
    {
      percentageUnigramsMatchedTitle =  numunigrams_matched_title / dbltotalunigrams;
      percentageUnigramsMatchedDesc = numunigrams_matched_desc / dbltotalunigrams;
      percentageUnigramsMatchedKeyword = numunigrams_matched_keyword / dbltotalunigrams;
      
      dbltotalunigrams -= 1.0;
      if(totalunigrams > 1)
      {
        percentageBigramsMatchedTitle = numbigrams_matched_title / dbltotalunigrams;
        percentageBigramsMatchedDesc = numbigrams_matched_desc / dbltotalunigrams;
        percentageBigramsMatchedKeyword = numbigrams_matched_keyword / dbltotalunigrams;
        
        dbltotalunigrams -= 1.0;
        if(totalunigrams > 2)
        {
          percentageTrigramsMatchedTitle = numtrigrams_matched_title / dbltotalunigrams;
          percentageTrigramsMatchedDesc = numtrigrams_matched_desc / dbltotalunigrams;
          percentageTrigramsMatchedKeyword = numtrigrams_matched_keyword / dbltotalunigrams;
        }
      }
    }
    
    target = 0.0, depthfeature = 0.0, positionfeature = 0.0;
    if(impressions > 0)target = clicks / (double)impressions;
    depthfeature = (MAX_AD_DEPTH + 1 - depth) / MAX_AD_DEPTH;
    positionfeature = (depth + 1 - position) / (double)depth;
    
    fout << target << " " << displayurlmap[displayurl] << " " << advertiserid << " " << depthfeature << " " << positionfeature << " " << keywordid << " " << adtitleid << " " << addescid << " " << userid;
    
    fout << " " << percentageUnigramsMatchedTitle << " " << percentageBigramsMatchedTitle << " " << percentageTrigramsMatchedTitle;
    fout << " " << percentageUnigramsMatchedDesc << " " << percentageBigramsMatchedDesc << " " << percentageTrigramsMatchedDesc;
    fout << " " << percentageUnigramsMatchedKeyword << " " << percentageBigramsMatchedKeyword << " " << percentageTrigramsMatchedKeyword;
    
    minlenquerytokens = querytokenids[queryid][0];
    if(minlenquerytokens > 10)minlenquerytokens = 10;
    FOR(i, 1, minlenquerytokens + 1)fout<< " " << querytokenids[queryid][i];
    
    fout << endl;
    
    if(lineno % 1000000 == 0)cout<<"Time taken to load "<< lineno <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
    if(lineno < 5)
    {
      dbg(clicks); dbg(impressions); dbg(displayurl); dbg(displayurlmap[displayurl]); dbge(advertiserid);
      dbg(depth); dbg(depthfeature); dbg(position); dbge(positionfeature);
      dbg(queryid); dbg(keywordid); dbg(adtitleid); dbg(addescid); dbg(userid); dbge(totalunigrams);
      // cout<<"Query Tokens"; FOR(i, 1, querytokenids[queryid][0] + 1)cout<<" "<<querytokenids[queryid][i]; cout<<endl;
      // cout<<"Ad Title Tokens"; FOR(i, 1, adtitletokenids[adtitleid][0] + 1)cout<<" "<<adtitletokenids[adtitleid][i]; cout<<endl;
      // cout<<"Ad Desc Tokens"; FOR(i, 1, addesctokenids[addescid][0] + 1)cout<<" "<<addesctokenids[addescid][i]; cout<<endl;
      // cout<<"Keyword Tokens"; FOR(i, 1, keywordtokenids[keywordid][0] + 1)cout<<" "<<keywordtokenids[keywordid][i]; cout<<endl;
      dbg(percentageUnigramsMatchedTitle); dbg(percentageBigramsMatchedTitle); dbge(percentageTrigramsMatchedTitle);
      dbg(percentageUnigramsMatchedDesc); dbg(percentageBigramsMatchedDesc); dbge(percentageTrigramsMatchedDesc);
      dbg(percentageUnigramsMatchedKeyword); dbg(percentageBigramsMatchedKeyword); dbge(percentageTrigramsMatchedKeyword);
    }
  }

  cout<<"Time taken to load "<< lineno <<" lines is: "<<(double)(clock()-start)/(double)CLOCKS_PER_SEC<<" seconds"<<endl;
  fout.close();
  fin.close();  
}

int main()
{
  Initialize();
  
  LoadQueryTokenMapping(QUERY_TOKENS_FILE);
  LoadAdTitleTokenMapping(ADTITLE_TOKENS_FILE);
  LoadAdDescriptionTokenMapping(ADDESCRIPTION_TOKENS_FILE);
  LoadKeywordTokenMapping(KEYWORD_TOKENS_FILE);
  LoadDisplayUrlMapping(DISPLAYURL_PROPERTIES_FILE);
  
  ComputeInteractionFeatures(TRAINING_FILE, OUTPUT_TRAINING_FILE, 2);
  ComputeInteractionFeatures(VALIDATION_FILE, OUTPUT_VALIDATION_FILE, 2);
  ComputeInteractionFeatures(TESTING_FILE, OUTPUT_TESTING_FILE, 2);
  ComputeInteractionFeatures(SUBMISSION_FILE, OUTPUT_SUBMISSION_FILE, 0);
  
  return 0;
}
