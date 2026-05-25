# C_server_speed_tests
Server internet download/upload tests, implemented in C programming language using libcurl and cJSON libraries <br>
## Dependencies <br>
Program depends on these Debian-based packages: <br>
1. `libcurl4-openssl-dev`
2. `libcjson-dev` 

To install these packages, run: <br>

`sudo apt install libcurl4-openssl-dev libcjson-dev -y`

## How to run

1. `git clone` and `cd` into the repo directory
2. run `make` to compile the program
3. run `./speed_test -a` to run all the tests (more options can be viewed with `-h` option)

## Example output result
```
./speed_test -a
Getting user's geolocation... OK.
Checking available servers by location... OK
   1. speedtest.litnet.lt:8080
   2. speed-kaunas.telia.lt:8080
   3. speedtest.kis.lt:8080
   4. sp1.kli.lt:8080
   5. stnet1.balticum.lt:8080
   6. speedtest.bacloud.com:8080
   7. speedtest1.ntt.lt:8080
   8. speedtest-vno.init.lt:8080
   9. speedtest.rackray.eu:8080
  10. speedtest.bite.lt:8080
  11. vln038-speedtest-1.tele2.net:8080
  12. speedtest-01.cgates.lt:8080
Checking for the best latency...
Testing [0001/12]:                           speedtest.litnet.lt:8080...OK (Connect time: 0.058339)
Testing [0002/12]:                         speed-kaunas.telia.lt:8080...OK (Connect time: 0.019006)
Testing [0003/12]:                              speedtest.kis.lt:8080...OK (Connect time: 0.020887)
Testing [0004/12]:                                    sp1.kli.lt:8080...OK (Connect time: 0.060571)
Testing [0005/12]:                            stnet1.balticum.lt:8080...OK (Connect time: 0.021762)
Testing [0006/12]:                         speedtest.bacloud.com:8080...OK (Connect time: 0.032023)
Testing [0007/12]:                             speedtest1.ntt.lt:8080...ERROR. (Couldn't connect to server)
Testing [0008/12]:                         speedtest-vno.init.lt:8080...OK (Connect time: 0.017008)
Testing [0009/12]:                          speedtest.rackray.eu:8080...ERROR. (Timeout was reached)
Testing [0010/12]:                             speedtest.bite.lt:8080...OK (Connect time: 0.111092)
Testing [0011/12]:                  vln038-speedtest-1.tele2.net:8080...ERROR. (Timeout was reached)
Testing [0012/12]:                        speedtest-01.cgates.lt:8080...ERROR. (Timeout was reached)
Checking download speed of host name... OK
Checking upload speed of host name... OK
RESULTS
----------
Download speed: 206.257536 Mb/s
Upload speed: 21.464336 Mb/s
Server name for speed test: speedtest-vno.init.lt:8080
User location: Lithuania
