using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LEDARRAY : MonoBehaviour
{

    [SerializeField] MessageListener messageListener;

    private void Start()
    {
        messageListener.SendTextData("%");
    }
}
