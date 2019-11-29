import smtplib 
import sys
from credentials import *

s = smtplib.SMTP('smtp.gmail.com', 587) 
  
s.starttls()
s.login(SENDER,PASSWORD)
message_detail = ''
for i in range(len(sys.argv)):
    if i > 2:
        message_detail += sys.argv[i] + ' '
RECEIVER  = sys.argv[1]
if sys.argv[2]== "REQUEST_ITEM_RETURN":
    MESSAGE ="Your request to return "+ message_detail.upper() + "has been approved By Inventory Manegement System, IIT Jodhpur."
elif sys.argv[2]== "REQUEST_ITEM":
    MESSAGE ="Your request to issue "+ message_detail.upper() + "has been approved By Inventory Manegement System, IIT Jodhpur."
else:
    MESSAGE ="Your request for membership in " + message_detail.upper() + "has been approved By Inventory Manegement System, IIT Jodhpur " 

s.sendmail(SENDER, RECEIVER , MESSAGE )  
s.quit()

NODES = [
'/home/kunal/work/blockchain/node1',
'/home/kunal/work/blockchain/node2',
'/home/kunal/work/blockchain/node3',
]
