# CWT-TH01S

**RS485 Modbus Water Proof Temperature Humidity Sensor Probe**

https://www.aliexpress.com/item/1005001404952412.html?spm=a2g0o.detail.1000014.9.29162c048oUA5v&gps-id=pcDetailBottomMoreOtherSeller&scm=1007.40050.281175.0&scm_id=1007.40050.281175.0&scm-url=1007.40050.281175.0&pvid=d833c160-1885-48d7-8094-82328fbb0317&_t=gps-id:pcDetailBottomMoreOtherSeller,scm-url:1007.40050.281175.0,pvid:d833c160-1885-48d7-8094-82328fbb0317,tpp_buckets:668%232846%238111%231996&pdp_ext_f=%7B%22sku_id%22%3A%2212000026105836717%22%2C%22sceneId%22%3A%2230050%22%7D&pdp_npi=2%40dis%21EUR%217.73%217.73%21%21%21%21%21%400b0a23a416607662172067140e5f73%2112000026105836717%21rec



https://store.comwintop.com/products/rs485-modbus-water-proof-temperature-humidity-sensor-probe?variant=42131365757155

**Wiring**



| **Cable color**     | **Description**  |
| ------------------- | ---------------- |
| Brown               | Power +(DC5-30V) |
| black               | Power -          |
| Yellow （or green） | RS485 A+         |
| Blue                | RS485 B-         |



RS485 communication Default
parameters: 4800,n,8,1

Default device address is 1

Modbus RTU protocol



![img](CWT-TH01S.assets/He51da2dba9844010935331f95475b875e-20220904190239771.png)



E.g. master read temperature humidity:

![img](CWT-TH01S.assets/H8bd835896aab4750b00002aa357b7388K-20220904190239730.jpg)



Sensor responds:

![img](CWT-TH01S.assets/H3383f57795534970a532c2c3492a54afw-20220904190239761.jpg)

Temperature calculates:

When temperature less than 0, value will be responded in complement 

Temperature: FF9F H= -97 => temperature= -9.7℃

hex to `int16_t`

Humidity: 1E6 H= 486 => humidity= 48.6%



**Set slave ID**

E.g., set slave ID=2, Master sends

![img](CWT-TH01S.assets/Hced823f310534a57b492d2d4a8a93567B-20220904190239736.png)



Sensor responds:

![img](CWT-TH01S.assets/H8123f5d7639a4ebb84795e97375506e2z-20220904190239748.png)



**Set baud rate**

E.g., set baud rate to 9600, Master sends

![img](CWT-TH01S.assets/H4877ed3a6e07453f9c4643ab6cc64a1cH-20220904190239751.png)



Sensor responds:

![img](CWT-TH01S.assets/H335b6e7c7dd84dbbab5200d65532a20aq-20220904190239763.png)



**Enquiry slave ID**

Master sends

![img](CWT-TH01S.assets/He7a497b9b7c3466d96f08fca00666236O-20220904190239765.png)



Sensor responds:

![img](CWT-TH01S.assets/H3450880e46ac47ac9f949a9d3309b24d6-20220904190239775.png)