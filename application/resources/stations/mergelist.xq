<stations>
{
for $doc in ('stations.qpl')
for $station in doc($doc)//station, 
    $stationcode in doc('stationcodes.qpl')//station[name = $station/name]
return
<station>
{$station/name}
{$station/pos}
{$stationcode/code}
</station>
}
{
for $doc in ('stations.qpl')
for $station in doc($doc)//station
let $stationcode := doc('stationcodes.qpl')//station[name != $station/name]
where
$station/name != $stationcode/name
return
<station>
{$station/name}
{$station/pos}
</station>
}
</stations>
