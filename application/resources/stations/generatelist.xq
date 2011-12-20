<stations>
{
for $doc in (
	'nord.osm',
	'nordovest.osm',
	'nordest.osm',
	'liguria.osm',
	'centronord.osm', 
	'centrosud.osm', 
	'sud.osm', 
	'sicilia.osm', 
	'puglia.osm', 
	'sardegna.osm',
	'h-nord.osm',
	'h-nordovest.osm',
	'h-nordest.osm',
	'h-liguria.osm',
	'h-centronord.osm', 
	'h-centrosud.osm', 
	'h-sud.osm', 
	'h-sicilia.osm', 
	'h-puglia.osm', 
	'h-sardegna.osm')
for $node in doc($doc)//node
where $node/tag[@k='name'] and (
fn:not(fn:exists($node//tag[@k='disused'])) or fn:contains($node//tag[@k='disused']/@v, 'no') 
) and (
$node/tag[@k='operator'] and (
fn:contains($node//tag[@k='operator']/@v, 'RFI') or 
fn:contains($node//tag[@k='operator']/@v, 'Centostazioni') or 
fn:contains($node//tag[@k='operator']/@v, 'Grandi Stazioni') or
fn:contains($node//tag[@k='operator']/@v, 'FNM') or
fn:contains($node//tag[@k='operator']/@v, 'FER') or
fn:contains($node//tag[@k='operator']/@v, 'RFT') or
fn:contains($node//tag[@k='operator']/@v, 'LFI')
))
return 
<station>
<pos>{
data($node/@lat)
},{
data($node/@lon)
}
</pos>
<name>{
if (fn:exists(data($node//tag[@k='name:rfi']))) then
	data($node//tag[@k='name:rfi']/@v)
else if (fn:exists(data($node//tag[@k='name:it']))) then
	data($node//tag[@k='name:it']/@v)
else
	data($node//tag[@k='name']/@v)
}</name>
</station>
}
</stations>
