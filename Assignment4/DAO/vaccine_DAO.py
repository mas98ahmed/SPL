# -*- coding: utf-8 -*-
"""
Created on Mon Jan 11 13:27:16 2021

@author: luee
"""

import datetime

class vaccine_DAO:
    _id: int
    _date: datetime
    _supplier: int
    _quantity: int

    def __init__(self, _id, _date, _supplier, _quantity):
        self._id = _id
        self._date = _date
        self._supplier = _supplier
        self._quantity = _quantity
        


        

    

#def main():
   # d = vaccine_DAO(1, None, 2, 3)
  #  dd = datetime.date.day
 #   print(dd)

#if __name__ == '__main__':
  #  main()