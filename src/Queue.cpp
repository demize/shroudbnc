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

#include "StdAfx.h"

/**
 * CQueue
 *
 * Constructs an empty queue.
 */
CQueue::CQueue() {
	// nothing to do here, really
}

/**
 * ~CQueue
 *
 * Destroy a queue.
 */
CQueue::~CQueue() {
	// same here
}

/**
 * PeekItems
 *
 * Retrieves the next item from the queue without removing it.
 */
const char *CQueue::PeekItem(void) {
	int LowestPriority = 99999;
	queue_item_t *ThatItem = NULL;

	for (unsigned int i = 0; i < m_Items.GetLength(); i++) {
		if (m_Items[i].Priority < LowestPriority) {
			LowestPriority = m_Items[i].Priority;
			ThatItem = m_Items.GetAddressOf(i);
		}
	}

	if (ThatItem != NULL) {
		return ThatItem->Line;
	} else {
		return NULL;
	}
}

/**
 * DequeueItem
 *
 * Retrieves the next item from the queue and removes it.
 */
char *CQueue::DequeueItem(void) {
	int Index;
	queue_item_t *Item = NULL;
	char *Line;

	for (unsigned int i = 0; i < m_Items.GetLength(); i++) {
		if (Item == NULL || m_Items[i].Priority < Item->Priority) {
			Item = m_Items.GetAddressOf(i);
			Index = i;
		}
	}

	if (Item != NULL) {
		Line = Item->Line;

		m_Items.Remove(Index);

		return Line;
	} else {
		return NULL;
	}
}

/**
 * QueueItem
 *
 * Inserts a new item at the end of the queue.
 *
 * @param Line the item which is to be inserted
 */
bool CQueue::QueueItem(const char *Line) {
	queue_item_t Item;

	if (Line == NULL) {
		return false;
	}

	Item.Line = strdup(Line);

	CHECK_ALLOC_RESULT(Item.Line, strdup) {
		return false;
	} CHECK_ALLOC_RESULT_END;

	Item.Priority = 0;

	for (unsigned int i = 0; i < m_Items.GetLength(); i++) {
		m_Items[i].Priority--;
	}

	return m_Items.Insert(Item);
}

/**
 * QueueItemNext
 *
 * Inserts a new item at the front of the queue.
 *
 * @param Line the item which is to be inserted
 */
bool CQueue::QueueItemNext(const char *Line) {
	for (unsigned int i = 0; i < m_Items.GetLength(); i++) {
		m_Items[i].Priority++;
	}

	return QueueItem(Line);
}

/**
 * GetLength
 *
 * Returns the number of items which are in the queue.
 */
unsigned int CQueue::GetLength(void) {
	return m_Items.GetLength();
}

/**
 * Clear
 *
 * Removes all items from the queue.
 */
void CQueue::Clear(void) {
	for (unsigned int i = 0; i < m_Items.GetLength(); i++) {
		free(m_Items[i].Line);
	}

}

bool CQueue::Freeze(CAssocArray *Box) {
	unsigned int i = 0;
	char *Line, *Index;

	while ((Line = DequeueItem()) != NULL) {
		asprintf(&Index, "%d", i);
		Box->AddString(Index, Line);
		free(Line);
		free(Index);
	}

	delete this;

	return true;
}

CQueue *CQueue::Unfreeze(CAssocArray *Box) {
	unsigned int i = 0;
	char *Index;
	const char *Line;
	CQueue *Queue;

	if (Box == NULL) {
		return NULL;
	}

	Queue = new CQueue();

	while (true) {
		asprintf(&Index, "%d", i);
		Line = Box->ReadString(Index);

		if (Line == NULL) {
			break;
		}

		Queue->QueueItem(Line);

		free(Index);

		i++;
	}

	return Queue;
}
