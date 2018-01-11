copy /Y mib.h mib.h.bak
del mib.h
copy /Y snmp.bib snmp.bib.bak 
del snmp.bib
mib2bib.exe script_snmp.mib
copy /Y snmp.bib "..\WebPage2+1"
