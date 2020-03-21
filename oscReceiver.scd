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
		var dur1, dur2;
		// "Collision: %".format(val).postln;
		if(val == true, {
			// Circle 1
			dur1 = ~radius1.linexp(0.0,1.0,0.0001,0.5);
			Synth(p.def("expodec", "sin"), [
				\dur, dur1,
				\sustain, dur1, 
				\freq, ~y1.linlin(0.0,1.0,0.85,0.25),
				\pan, ~x1,
				\amp, 0.35
			]);

			// Circle 2
			dur2 = ~radius2.linexp(0.0,1.0,0.0001,0.5);
			Synth(p.def("expodec", "fm"), [
				\dur, dur2,
				\sustain, dur2, 
				\freq, ~y2.linlin(0.0,1.0,0.995,0.5),
				\index1, 0.5+~x1,
				\index2, 1+~y1,
				\pan, ~x2,
				\amp, 0.15
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


	// circle 2
	OSCdef.new(\x2, {|...args|
		var val = args[0][1];
		// "x2: %".format(val).postln;
		~x2 = val;
	}, ~ofRoot ++"/2/x");

	OSCdef.new(\y2, {|...args|
		var val = args[0][1];
		// "y2: %".format(val).postln;
		~y2 = val
	}, ~ofRoot ++"/2/y");

	OSCdef.new(\radius2, {|...args|
		var val = args[0][1];
		// "radius: %".format(val).postln;
		~radius2 = val;
	}, ~ofRoot ++"/2/radius");
)
)
