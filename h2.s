#by zaz, still not as good as rainbowdash though
#2013

.name		"helltrain"
.comment	"choo-choo, motherf*****s !"

entry:
	ld		%0, r16
	fork	%:cc_spawn

wall_prep:
	ld		%0, r2
	ld		%0, r16

wall:
	live	%4902343
	zjmp	%:wall

beegees_gen:
	live	%4239423
	fork	%:beegees_gen
	ld		%0, r16

beegees:
	live	%3442302
	zjmp	%:beegees

cc_spawn:
	live	%4320423
	zjmp	%3
	fork	%:cc_spawn

cc4:
	live	%4329034
	fork	%:cc3
	live	%3401123
	fork	%:cc2
	live	%4590543
	fork	%:cc1
cc4ld:
	ld		%0, r2
	ld		%251883523, r3
	ld		%0, r16
cc4l:
	live	%4930423	
	ld		%0, r16
	zjmp	%:choochoo

cc2:
	live	%4342342
	fork	%:wall_prep
	ld		%251883523, r2
	ld		%386101251, r3
	ld		%0, r16
	ld		%0, r16
	zjmp	%:choochoo

cc3:
	live	%4239013
	fork	%:cc4
	live	%4093282
	fork	%:beegees_gen
	ld		%4294902016, r2
	ld		%436432899, r3
	ld		%0, r16
	ld		%0, r16
	ld		%0, r16
	zjmp	%:choochoo

cc1:
	ld		%57672192, r2
	ld		%318992387, r3
	ld		%0, r16
	zjmp	%:choochoo

choochoo:
	st		r2, 15
	st		r3, -1
cc_live:
	live	%0
