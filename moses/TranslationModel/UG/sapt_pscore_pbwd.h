//-*- c++ -*-
// written by Ulrich Germann
#pragma once
#include "moses/TranslationModel/UG/mm/ug_bitext.h"
#include "util/exception.hh"
#include "boost/format.hpp"
#include "boost/foreach.hpp"

namespace Moses {
  namespace bitext
  {
    template<typename Token>
    class
    PScorePbwd : public PhraseScorer<Token>
    {
      float   conf;
      string denom;

    public:
      PScorePbwd(float const c, string d)
      {
	this->m_index = -1;
	conf  = c;
	denom = d;
	size_t checksum = d.size();
	BOOST_FOREACH(char const& x, denom)
	  {
	    if (x == '+') { --checksum; continue; }
	    if (x != 'g' && x != 's' && x != 'r') continue;
	    string s = (format("pbwd-%c%.3f") % x % c).str();
	    this->m_feature_names.push_back(s);
	  }
	this->m_num_feats = this->m_feature_names.size();
	UTIL_THROW_IF2(this->m_feature_names.size() != checksum,
		       "Unknown parameter in specification '"
		       << d << "' for Pbwd phrase scorer at " << HERE);
      }

      void
      operator()(Bitext<Token> const& bt,
		 PhrasePair<Token>& pp,
		 vector<float> * dest = NULL) const
      {
	if (!dest) dest = &pp.fvals;
	// we use the denominator specification to scale the raw counts on the
	// target side; the clean way would be to counter-sample
	size_t i = this->m_index;
	BOOST_FOREACH(char const& x, denom)
	  {
	    uint32_t m2 = pp.raw2;
	    if      (x == 'g') m2 = round(m2 * float(pp.good1)   / pp.raw1);
	    else if (x == 's') m2 = round(m2 * float(pp.sample1) / pp.raw1);
	    (*dest)[i++] = log(lbop(max(m2, pp.joint),pp.joint,conf));
	  }
      }
    };
  } // namespace bitext
} // namespace Moses
