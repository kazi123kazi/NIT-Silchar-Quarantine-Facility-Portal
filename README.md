# NIT-Silchar-Quarantine-Facility-Portal
A console application using CPP that manages the guest details and check in and quarantine period of individual(14 days). Efficient searching of guest, sorting and availability of room details can be found using the applications. <br>
A quarantine facility has been set
up at NIT Silchar, which can accommodate a maximum of 500 people. As per the district administration, only the flight bound male-passengers without any accompanying children arriving at Silchar airport will likely be quarantined for 14 days.Each quarantined person will be allotted a single room for his stay at the quarantine centre for the said period.  The rooms in the facility are of single occupancy and the rooms are numbered from 81 to 580. Once the quarantine period is over, a quarantined person(s) are discharged from the quarantine centre after vacating his room. So, the figure of occupied rooms keeps on changing after a certain period of time. Subject to the availability of rooms in the quarantine centre, each day a limited no. of passengers are directed to the quarantine facility at NIT Silchar.
<br>
The nodal officer who administers the quarantine centre has to keep track of the records of the quarantined persons like:
*Name Of The Person
*Address
*Age
*Arrival Date
*Arrival Month
*Allotted Room Number
*Discharged Date
*Discharged Month etc.
<br>
In this project, I attempt to solve this practical problem by using a data container to store the respective patient’s record; giving the user the ability to search any patient’s records using their name and address; the ability to sort the records with respect to their allotted room numbers; and the feature to display the list of occupied and vacant rooms.

#FUNCTIONALITIES
The user is presented with the following 6 options after logging in:
##1) Check In a new guest:
Adds a new patient into the facility. On choosing this the operator
will be prompted to enter the details of the incoming guest such as
Name, Check in and Check out Dates, Address, Age etc. and will be
allotted a room number.
After this step is complete, the new guest is added to the queue.
##2) Sort the guest list:
Sorts the guest list and displays the sorted list on the screen.
Sorting can be done on the basis of:
· Name of the guest
· Room number
depending on what the operator wants.
Further, while displaying the sorted list, the operator can choose
what attributes of each guest will/will not be displayed.
##3) Search for a guest:
Like sorting, searching a guest can also be done on the basis of
· Name of the patient
· Room Number
The guest who matches the input provided by the operator is
displayed on the screen.
If there are multiple guests who match the criteria, all of them are
displayed.
##4) Display Vacant and Occupied Rooms:
Provides a list of all occupied and vacant rooms at the time of this
option being selected.
##5) Display information of all guests:
Displays the information of all guests currently in the facility.
##6) Exit the portal:
Used to terminate the program and exit the portal.
