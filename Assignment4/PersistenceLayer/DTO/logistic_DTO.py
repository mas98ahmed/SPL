# -*- coding: utf-8 -*-
"""
Created on Mon Jan 11 13:27:56 2021

@author: luee
"""

class logistic_DTO:
    _id: int
    _name: str
    _count_sent: int
    _count_received: int
    def __init__(self, _id, _name, _count_sent, _count_received):
        self._id = _id
        self._name = _name
        self._count_sent = _count_sent
        self._count_received = _count_received