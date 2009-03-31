/*
 * opencog/embodiment/PetaverseProxySimulator/InterfaceListenerAgent.h
 *
 * Copyright (C) 2007-2008 Andre Senna
 * All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License v3 as
 * published by the Free Software Foundation and including the exceptions
 * at http://opencog.org/wiki/Licenses
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program; if not, write to:
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef INTERFACELISTENERAGENT_H
#define INTERFACELISTENERAGENT_H

#include <opencog/server/Agent.h>

namespace PetaverseProxySimulator {

using namespace opencog;

class InterfaceListenerAgent : public Agent {

    private:

    public:

        virtual const ClassInfo& classinfo() const { return info(); }
        static const ClassInfo& info() {
            static const ClassInfo _ci("PetaverseProxySimulator::MessageSenderAgent");
            return _ci;
        }

        // ***********************************************/
        // Constructors/destructors

        ~InterfaceListenerAgent();
        InterfaceListenerAgent();

        void run(CogServer *ne);

}; // class
}  // namespace

#endif
