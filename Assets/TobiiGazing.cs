using Tobii.Gaming;
using UnityEngine;

public class TobiiGazing : MonoBehaviour
{
    public GameObject GazePoint;

    private void Update()
    {
        GazePoint gazePoint = TobiiAPI.GetGazePoint();

        // Rotate the transform this script is on, to look at where the user is gazing

        if (gazePoint.IsValid)
        {
            Vector3 screenPoint = new Vector3(gazePoint.Screen.x, gazePoint.Screen.y, 10f);
            Vector3 worldPoint = Camera.main.ScreenToWorldPoint(screenPoint);
            transform.LookAt(worldPoint);
        }
    }
}
