using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class Rotator : MonoBehaviour
{
    [SerializeField] private Transform leftHandTrans;
    [SerializeField] private Transform rightHandTrans;

    void Update()
    {
        transform.rotation = rightHandTrans.rotation;
    }
}
