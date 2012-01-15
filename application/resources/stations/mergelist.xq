<stations>
{
for $station in doc('stationpositions.qpl')//station
return
<station>
{ $station/name }
{ $station/pos }
{for $stationcode in doc('stationcodes.qpl')//station
where $stationcode/name = $station/name
return $stationcode/code}
</station>
}
</stations>
