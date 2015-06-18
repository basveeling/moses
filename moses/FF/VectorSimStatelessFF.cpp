#include <vector>
#include "VectorSimStatelessFF.h"
#include "moses/ScoreComponentCollection.h"
#include "moses/TargetPhrase.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <stdio.h>

using namespace std;

namespace Moses
{


VectorSimStatelessFF::VectorSimStatelessFF(const std::string &line)
  :StatelessFeatureFunction(2, line)
{
  ReadParameters();
  printf("TESTING DATE3");
  FILE *fp,*outputfile;
  char var[40];

  fp = popen("date +%s", "r");
  while (fgets(var, sizeof(var), fp) != NULL)
    {
      printf("%s", var);
    }
  pclose(fp);
}

void VectorSimStatelessFF::EvaluateInIsolation(const Phrase &source
    , const TargetPhrase &targetPhrase
    , ScoreComponentCollection &scoreBreakdown
    , ScoreComponentCollection &estimatedFutureScore) const
{
  // dense scores
  vector<float> newScores(m_numScoreComponents);
  newScores[0] = 1.5;
  scoreBreakdown.PlusEquals(this, newScores);

  // sparse scores
  scoreBreakdown.PlusEquals(this, "sparse-name", 2.4);
  printf("TESTING DATE1");
  FILE *fp,*outputfile;
  char var[40];

  fp = popen("date +%s", "r");
  while (fgets(var, sizeof(var), fp) != NULL)
    {
      printf("%s", var);
    }
  pclose(fp);
}

void VectorSimStatelessFF::EvaluateWithSourceContext(const InputType &input
    , const InputPath &inputPath
    , const TargetPhrase &targetPhrase
    , const StackVec *stackVec
    , ScoreComponentCollection &scoreBreakdown
    , ScoreComponentCollection *estimatedFutureScore) const
{
  if (targetPhrase.GetNumNonTerminals()) {
    vector<float> newScores(m_numScoreComponents);
    newScores[0] = - std::numeric_limits<float>::infinity();
    scoreBreakdown.PlusEquals(this, newScores);
  }
  printf("TESTING DATE2");
  FILE *fp,*outputfile;
  char var[40];

  fp = popen("date +%s", "r");
  while (fgets(var, sizeof(var), fp) != NULL)
    {
      printf("%s", var);
    }
  pclose(fp);
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
  if (key == "arg") {
    // set value here
  } else {
    StatelessFeatureFunction::SetParameter(key, value);
  }
}

}

