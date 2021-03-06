#include <vector>
#include "VectorSimStatelessFF.h"
#include "moses/ScoreComponentCollection.h"
#include "moses/TargetPhrase.h"
#include <cstdlib>
#include <string>
#include <boost/format.hpp>
#include "../StaticData.h"
#include <iostream>
#include <stdio.h>

using namespace std;

namespace Moses
{


VectorSimStatelessFF::VectorSimStatelessFF(const std::string &line)
  :StatelessFeatureFunction(1, line)
{
  ReadParameters();
}

void VectorSimStatelessFF::EvaluateInIsolation(const Phrase &source
    , const TargetPhrase &targetPhrase
    , ScoreComponentCollection &scoreBreakdown
    , ScoreComponentCollection &estimatedFutureScore) const
{

  std::vector<FactorType> outputFactorOrder = StaticData::Instance().GetOutputFactorOrder();
  std::string phrase_source = source.GetStringRep(outputFactorOrder);
  std::string phrase_target = targetPhrase.GetStringRep(outputFactorOrder);
  FILE *fp,*outputfile;

  char var[10];
  float score = 0.0;
  try{
      std::string command_str("/home/veeling/nlp2-lab/get_sim.sh \"");
      command_str.append(phrase_source.c_str());
      command_str.append("\" \"");
      command_str.append(phrase_target.c_str());
      command_str.append("\"");
      fp = popen(command_str.c_str(), "r");
      while (fgets(var, sizeof(var), fp) != NULL) {}
      std::cerr << "Parsing this: ";
      std::cerr << std::string(var);
      score = std::stof(std::string(var));

      std::cerr << "Getting sim for " << phrase_source.c_str() << ", " << phrase_target.c_str() << "\n";
      std::cerr << "Sim Score = " << score;
  } catch( ... ) {
       std::cerr << L"error parsing! " << phrase_source.c_str() << ", " << phrase_target.c_str() << "\n";
  }
  // dense scores
  vector<float> newScores(m_numScoreComponents);
  newScores[0] = score;
  scoreBreakdown.PlusEquals(this, newScores);
}

void VectorSimStatelessFF::EvaluateWithSourceContext(const InputType &input
    , const InputPath &inputPath
    , const TargetPhrase &targetPhrase
    , const StackVec *stackVec
    , ScoreComponentCollection &scoreBreakdown
    , ScoreComponentCollection *estimatedFutureScore) const
{
//  if (targetPhrase.GetNumNonTerminals()) {
//    vector<float> newScores(m_numScoreComponents);
//    newScores[0] = - std::numeric_limits<float>::infinity();
//    scoreBreakdown.PlusEquals(this, newScores);
//  }
//  printf("TESTING DATE2");
//  FILE *fp,*outputfile;
//  char var[40];
//
//  fp = popen("date +%s", "r");
//  while (fgets(var, sizeof(var), fp) != NULL)
//    {
//      printf("%s", var);
//    }
//  pclose(fp);
}

void VectorSimStatelessFF::EvaluateTranslationOptionListWithSourceContext(const InputType &input

    , const TranslationOptionList &translationOptionList) const
{}

void VectorSimStatelessFF::EvaluateWhenApplied(const Hypothesis& hypo,
    ScoreComponentCollection* accumulator) const
{}

void VectorSimStatelessFF::EvaluateWhenApplied(const ChartHypothesis &hypo,
    ScoreComponentCollection* accumulator) const
{}

void VectorSimStatelessFF::SetParameter(const std::string& key, const std::string& value)
{
//  if (key == "arg") {
//    // set value here
//  } else {
//    StatelessFeatureFunction::SetParameter(key, value);
//  }
}

}

