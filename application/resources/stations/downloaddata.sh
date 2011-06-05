#! /bin/sh
curl --location --globoff "http://jxapi.openstreetmap.org/xapi/api/0.6/node[railway=station][bbox=6.7,44,10,46]" -o nordovest.osm &
curl --location --globoff "http://jxapi.openstreetmap.org/xapi/api/0.6/node[railway=station][bbox=10,44,14,46]" -o nordest.osm &
curl --location --globoff "http://jxapi.openstreetmap.org/xapi/api/0.6/node[railway=station][bbox=10,42,15,44]" -o centronord.osm &
curl --location --globoff "http://jxapi.openstreetmap.org/xapi/api/0.6/node[railway=station][bbox=12,40,17,42]" -o centrosud.osm &
curl --location --globoff "http://jxapi.openstreetmap.org/xapi/api/0.6/node[railway=station][bbox=12.3,38,17.3,40]" -o sud.osm &
curl --location --globoff "http://jxapi.openstreetmap.org/xapi/api/0.6/node[railway=station][bbox=12,36.5,16.5,38]" -o sicilia.osm &
curl --location --globoff "http://jxapi.openstreetmap.org/xapi/api/0.6/node[railway=station][bbox=17.3,39.5,19,41]" -o puglia.osm &
curl --location --globoff "http://jxapi.openstreetmap.org/xapi/api/0.6/node[railway=station][bbox=8,38.7,10,41.3]" -o sardegna.osm
