/*******************************************************************************
 * shroudBNC - an object-oriented framework for IRC                            *
 * Copyright (C) 2005 Gunnar Beutner                                           *
 *                                                                             *
 * This program is free software; you can redistribute it and/or               *
 * modify it under the terms of the GNU General Public License                 *
 * as published by the Free Software Foundation; either version 2              *
 * of the License, or (at your option) any later version.                      *
 *                                                                             *
 * This program is distributed in the hope that it will be useful,             *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with this program; if not, write to the Free Software                 *
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. *
 *******************************************************************************/

/**
 * CDnsEvents
 *
 * An interface for adns events.
 */
struct CDnsEvents {
	/**
	 * AsyncDnsFinished
	 *
	 * This function is executed when the adns query is finished or the query
	 * timed out.
	 * @param Query the adns query
	 * @param Response the associated response, can be NULL
	 */
	virtual void AsyncDnsFinished(adns_query *Query, adns_answer *Response) = 0;

	/**
	 * Destroy
	 *
	 * Destroys the event object.
	 */
	virtual void Destroy(void) = 0;
};

/**
 * IMPL_DNSEVENTCLASS
 *
 * Implements the CDnsEvents interface.
 *
 * @param ClassName the name of the class which is to be created
 * @param EventClassName the name of the class which events should be passed to
 * @param Function the name of the function in that class
 */
#define IMPL_DNSEVENTCLASS(ClassName, EventClassName, Function) \
class ClassName : public CDnsEvents { \
private: \
	EventClassName *m_EventObject; \
\
	virtual void AsyncDnsFinished(adns_query *Query, adns_answer *Response) { \
		m_EventObject->Function(Query, Response); \
	} \
public: \
	ClassName(EventClassName* EventObject) { \
		m_EventObject = EventObject; \
	} \
\
	void Destroy(void) { \
		delete this; \
	} \
};
