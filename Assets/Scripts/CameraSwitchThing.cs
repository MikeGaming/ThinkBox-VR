using System.Collections;
using UnityEngine;

public class CameraSwitchThing : MonoBehaviour
{
    [SerializeField] Camera cam;

    private void Start()
    {
        StartCoroutine(ChangeRenderEye());
    }

    IEnumerator ChangeRenderEye()
    {
        yield return new WaitForSeconds(5);
        cam.stereoTargetEye = StereoTargetEyeMask.None;
    }
}
