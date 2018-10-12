/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2009 Ferdinando Ametrano
 Copyright (C) 2005 Joseph Wang

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <ql/event.hpp>
#include <ql/patterns/visitor.hpp>
#include <ql/settings.hpp>

namespace QuantLib {

    bool Event::hasOccurred(const Date& d, // refDate
                            boost::optional<bool> includeRefDate) const {
        Date refDate =
            d != Date() ? d : Settings::instance().evaluationDate();
        bool includeRefDateEvent =
            includeRefDate ? *includeRefDate :
                           Settings::instance().includeReferenceDateEvents();
        if (includeRefDateEvent)
            return date() < refDate;
        else
            return date() <= refDate;
    }

    void Event::accept(AcyclicVisitor& v) {
        auto* v1 = dynamic_cast<Visitor<Event>*>(&v);
        if (v1 != 0)
            v1->visit(*this);
        else
            QL_FAIL("not an event visitor");
    }

}
