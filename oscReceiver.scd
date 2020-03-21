/*

OSC Receiver for collision circles program in open frameworks

*/
// Setup
(
	s.waitForBoot{
		if(Quarks.isInstalled("Particular").not, {
			Quarks.install("https://github.com/madskjeldgaard/Particular.git");
		}, {
			p = Particular.new(2);
			~thisPort = 1210;
			thisProcess.openUDPPort(~thisPort);
		}
	})
)
(
	~ofRoot = "/of/circle";

	OSCdef.new(\col1, {|...args|
		var val = args[0][1];
		var dur;
		// "Collision: %".format(val).postln;
		if(val == true, {
			dur = ~radius1.linexp(0.0,1.0,0.0001,0.25);

			Synth(p.def("expodec", "sin"), [
				\dur, dur,
				\sustain, dur, 
				\freq, ~y1.linlin(0.0,1.0,0.95,0.35),
				\pan, ~x1,
				\amp, 0.35
			])
		})

	}, ~ofRoot ++"/1/collision");

	OSCdef.new(\x1, {|...args|
		var val = args[0][1];
		// "x1: %".format(val).postln;
		~x1 = val;
	}, ~ofRoot ++"/1/x");

	OSCdef.new(\y1, {|...args|
		var val = args[0][1];
		// "y1: %".format(val).postln;
		~y1 = val
	}, ~ofRoot ++"/1/y");

	OSCdef.new(\radius1, {|...args|
		var val = args[0][1];
		// "radius: %".format(val).postln;
		~radius1 = val;
	}, ~ofRoot ++"/1/radius");
)
