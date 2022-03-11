package com.example.camerajni;

import androidx.appcompat.app.AppCompatActivity;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.widget.TextView;

import com.example.camerajni.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'camerajni' library on application startup.
    static {
        System.loadLibrary("camerajni");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        String camPerm = Manifest.permission.CAMERA;
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        String [] arr = new String[1];
        arr[0] = camPerm;
        if (checkSelfPermission(camPerm) == PackageManager.PERMISSION_DENIED) {
            requestPermissions(arr, 666);
        }
        Boolean val = checkSelfPermission(arr[0]) == PackageManager.PERMISSION_GRANTED;
        tv.setText(getCum());
    }

    /**
     * A native method that is implemented by the 'camerajni' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native String getCum();
}