		    var max_a=0.0;
            var max_b=0.0;
            var max_g=0.0;

    function init() {
      //Find our div containers in the DOM
      var dataContainerOrientation = document.getElementById('dataContainerOrientation');
      var dataContainerMotion = document.getElementById('dataContainerMotion');
      //Check for support for DeviceOrientation event
      if(window.DeviceOrientationEvent) {
        window.addEventListener('deviceorientation', function(event) {
                var alpha = event.alpha;
                var beta = event.beta;
                var gamma = event.gamma;

                //print
                if(alpha!=null || beta!=null || gamma!=null)
                  dataContainerOrientation.innerHTML = 'alpha: ' + alpha + '<br/>beta: ' + beta + '<br />gamma: ' + gamma;
              }, false);
      }
      // Check for support for DeviceMotion events
      if(window.DeviceMotionEvent) {
      window.addEventListener('devicemotion', function(event) {
                var x = event.accelerationIncludingGravity.x;
                var y = event.accelerationIncludingGravity.y;
                var z = event.accelerationIncludingGravity.z;
                var r = event.rotationRate;
                if (max_a<r.alpha) max_a=r.alpha;
                if (max_b<r.beta)  max_b=r.beta;
                if (max_g<r.gamma)  max_g=r.gamma;
                //shake triggered
                if (max_g > 10.0){
                    Android.showToast(max_g);
                    max_g = 0.0;
                    Android.ding();
                }
                //print
                var html = 'Acceleration:<br />';
                html += 'x: ' + x +'<br />y: ' + y + '<br/>z: ' + z+ '<br />';
                html += 'Rotation rate:<br />';
                if(r!=null) html += 'alpha: ' + r.alpha
                +'<br />beta: ' + r.beta
                + '<br/>gamma: ' + r.gamma
                + '<br/>max_a: ' + max_a
                + '<br/>max_b: ' + max_b
                + '<br/>max_g: ' + max_g;
                dataContainerMotion.innerHTML = html;
              });
      }
}