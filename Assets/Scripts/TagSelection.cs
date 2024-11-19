using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TagSelection : MonoBehaviour
{

    Image selectImage;
    bool isTriggered;

    // Start is called before the first frame update
    void Start()
    {
        selectImage = GetComponent<Image>();
    }

    public void ToggleColour()
    {
        isTriggered = !isTriggered;
        if (isTriggered)
        {
            selectImage.color = Color.green;
        }
        else
        {
            selectImage.color = Color.white;
        }
    }
}
